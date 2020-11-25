#include "formats/cdfs.h"

#include <retro_miscellaneous.h>
#include <compat/strl.h>
#include <file/file_path.h>
#include <string/stdstring.h>

static void cdfs_determine_sector_size(cdfs_file_t* file)
{
   uint8_t buffer[32];
   int64_t stream_size;

   /* MODE information is normally found in the CUE sheet, but we can try to determine it from the raw data.
    *
    *   MODE1/2048 - CDROM Mode1 Data (cooked) [no header, no footer]
    *   MODE1/2352 - CDROM Mode1 Data (raw)    [16 byte header, 288 byte footer]
    *   MODE2/2336 - CDROM-XA Mode2 Data       [8 byte header, 280 byte footer]
    *   MODE2/2352 - CDROM-XA Mode2 Data       [24 byte header, 280 byte footer]
    *
    * Note that MODE is actually a property on each sector and can change between 1 and 2 depending on how much error
    * correction the author desired. To support that, the data format must be "/2352" to include the full header and
    * data without error correction information, at which point the CUE sheet information becomes just a hint.
    */

   /* The boot record or primary volume descriptor is always at sector 16 and will contain a "CD001" marker */
   intfstream_seek(file->stream, 16 * 2352, SEEK_SET);
   if (intfstream_read(file->stream, buffer, sizeof(buffer)) < sizeof(buffer))
      return;

   /* if this is a CDROM-XA data source, the "CD001" tag will be 25 bytes into the sector */
   if (buffer[25] == 0x43 && buffer[26] == 0x44 &&
      buffer[27] == 0x30 && buffer[28] == 0x30 && buffer[29] == 0x31)
   {
      file->stream_sector_size = 2352;
      file->stream_sector_header_size = 24;
   }
   /* otherwise it should be 17 bytes into the sector */
   else if (buffer[17] == 0x43 && buffer[18] == 0x44 &&
      buffer[19] == 0x30 && buffer[20] == 0x30 && buffer[21] == 0x31)
   {
      file->stream_sector_size = 2352;
      file->stream_sector_header_size = 16;
   }
   else
   {
      /* ISO-9660 says the first twelve bytes of a sector should be the sync pattern 00 FF FF FF FF FF FF FF FF FF FF 00 */
      if (buffer[0] == 0 && buffer[1] == 0xFF && buffer[2] == 0xFF && buffer[3] == 0xFF &&
         buffer[4] == 0xFF && buffer[5] == 0xFF && buffer[6] == 0xFF && buffer[7] == 0xFF &&
         buffer[8] == 0xFF && buffer[9] == 0xFF && buffer[10] == 0xFF && buffer[11] == 0)
      {
         /* don't actually expect to get here - a properly headered sector should have had the CD001 tag */

         /* after the 12 byte sync pattern is three bytes identifying the sector and then one byte for the mode (total 16 bytes) */
         file->stream_sector_size = 2352;
         file->stream_sector_header_size = 16;
      }
      else
      {
         /* no recognizable header - attempt to determine sector size from stream size */
         stream_size = intfstream_get_size(file->stream);

         if ((stream_size % 2352) == 0)
         {
            /* audio tracks use all 2352 bytes without a header */
            file->stream_sector_size = 2352;
         }
         else if ((stream_size % 2048) == 0)
         {
            /* cooked tracks eliminate all header/footer data */
            file->stream_sector_size = 2048;
         }
         else if ((stream_size % 2336) == 0)
         {
            /* MODE 2 format without 16-byte sync data */
            file->stream_sector_size = 2336;
            file->stream_sector_header_size = 8;
         }
      }
   }
}

static void cdfs_seek_sector(cdfs_file_t* file, unsigned int sector)
{
   intfstream_seek(file->stream, sector * file->stream_sector_size + file->stream_sector_header_size, SEEK_SET);
}

static int cdfs_find_file(cdfs_file_t* file, const char* path)
{
   uint8_t buffer[2048], *tmp;
   int sector, path_length;

   const char* slash = strrchr(path, '\\');
   if (slash)
   {
      /* navigate the path to the directory record for the file */
      const int dir_length = (int)(slash - path);
      memcpy(buffer, path, dir_length);
      buffer[dir_length] = '\0';

      sector = cdfs_find_file(file, (const char*)buffer);
      if (sector < 0)
         return sector;

      path += dir_length + 1;
   }
   else
   {
      int offset;

      /* find the cd information (always 16 frames in) */
      cdfs_seek_sector(file, 16);
      intfstream_read(file->stream, buffer, sizeof(buffer));

      /* the directory_record starts at 156 bytes into the sector.
       * the sector containing the root directory contents is a 3 byte value that is 2 bytes into the directory_record. */
      offset = 156 + 2;
      sector = buffer[offset] | (buffer[offset + 1] << 8) | (buffer[offset + 2] << 16);
   }

   /* process the contents of the directory */
   cdfs_seek_sector(file, sector);
   intfstream_read(file->stream, buffer, sizeof(buffer));

   path_length = strlen(path);
   tmp = buffer;
   while (tmp < buffer + sizeof(buffer))
   {
      /* the first byte of the record is the length of the record - if 0, we reached the end of the data */
      if (!*tmp)
         break;

      /* filename is 33 bytes into the record and the format is "FILENAME;version" or "DIRECTORY" */
      if ((tmp[33 + path_length] == ';' || tmp[33 + path_length] == '\0') &&
         strncasecmp((const char*)(tmp + 33), path, path_length) == 0)
      {
         /* the file size is in bytes 10-13 of the record */
         if (!slash)
            file->size = tmp[10] | (tmp[11] << 8) | (tmp[12] << 16) | (tmp[13] << 24);

         /* the file contents are in the sector identified in bytes 2-4 of the record */
         sector = tmp[2] | (tmp[3] << 8) | (tmp[4] << 16);
         return sector;
      }

      /* the first byte of the record is the length of the record */
      tmp += tmp[0];
   }

   return -1;
}

int cdfs_open_file(cdfs_file_t* file, intfstream_t* stream, const char* path)
{
   if (!file || !stream)
      return 0;

   memset(file, 0, sizeof(*file));

   file->stream = stream;
   cdfs_determine_sector_size(file);

   file->current_sector = -1;
   if (path != NULL)
   {
      file->first_sector = cdfs_find_file(file, path);
   }
   else if (file->stream_sector_size)
   {
      file->first_sector = 0;
      file->size = (intfstream_get_size(file->stream) / file->stream_sector_size) * 2048;
   }
   else
   {
      file->first_sector = -1;
   }

   return (file->first_sector >= 0);
}

int64_t cdfs_read_file(cdfs_file_t* file, void* buffer, uint64_t len)
{
   int bytes_read = 0;

   if (!file || file->first_sector < 0 || !buffer)
      return 0;

   if (len > file->size - file->pos)
      len = file->size - file->pos;

   if (len == 0)
      return 0;

   if (file->sector_buffer_valid)
   {
      size_t remaining = 2048 - file->current_sector_offset;
      if (remaining > 0)
      {
         if (remaining >= len)
         {
            memcpy(buffer, &file->sector_buffer[file->current_sector_offset], len);
            file->current_sector_offset += len;
            return len;
         }

         memcpy(buffer, &file->sector_buffer[file->current_sector_offset], remaining);
         buffer = (char*)buffer + remaining;
         bytes_read += remaining;
         len -= remaining;

         file->current_sector_offset += remaining;
      }

      ++file->current_sector;
      file->current_sector_offset = 0;
      file->sector_buffer_valid = 0;
   }
   else if (file->current_sector < file->first_sector)
   {
      file->current_sector = file->first_sector;
      file->current_sector_offset = 0;
   }

   while (len >= 2048)
   {
      cdfs_seek_sector(file, file->current_sector);
      intfstream_read(file->stream, buffer, 2048);

      buffer = (char*)buffer + 2048;
      bytes_read += 2048;
      ++file->current_sector;

      len -= 2048;
   }

   if (len > 0)
   {
      cdfs_seek_sector(file, file->current_sector);
      intfstream_read(file->stream, file->sector_buffer, 2048);
      memcpy(buffer, file->sector_buffer, len);
      file->current_sector_offset = len;
      file->sector_buffer_valid   = 1;

      bytes_read += len;
   }

   file->pos += bytes_read;
   return bytes_read;
}

void cdfs_close_file(cdfs_file_t* file)
{
   if (file)
   {
      /* not really anything to do here, just clear out the first_sector so read() won't do anything */
      file->first_sector = -1;
   }
}

int64_t cdfs_get_size(cdfs_file_t* file)
{
   if (!file || file->first_sector < 0)
      return 0;

   return file->size;
}

int64_t cdfs_tell(cdfs_file_t* file)
{
   if (!file || file->first_sector < 0)
      return -1;

   return file->pos;
}

int64_t cdfs_seek(cdfs_file_t* file, int64_t offset, int whence)
{
   int64_t new_pos;
   int new_sector;

   if (!file || file->first_sector < 0)
      return -1;

   switch (whence)
   {
      case SEEK_SET:
         new_pos = offset;
         break;

      case SEEK_CUR:
         new_pos = file->pos + offset;
         break;

      case SEEK_END:
         new_pos = file->size - offset;
         break;

      default:
         return -1;
   }

   if (new_pos < 0)
      return -1;
   else if (new_pos > file->size)
      return -1;

   file->pos = (unsigned int)new_pos;
   file->current_sector_offset = file->pos % 2048;

   new_sector = file->pos / 2048;
   if (new_sector != file->current_sector)
   {
      file->current_sector = new_sector;
      file->sector_buffer_valid = false;
   }

   return 0;
}

static void cdfs_skip_spaces(const char** ptr)
{
   while (**ptr && (**ptr == ' ' || **ptr == '\t'))
      ++(*ptr);
}

static intfstream_t* cdfs_open_cue_track(const char* path, unsigned int track_index)
{
   char* cue_contents = NULL;
   char* cue = NULL;
   const char* line = NULL;
   int found_track = 0;
   char current_track_path[PATH_MAX_LENGTH] = {0};
   char track_path[PATH_MAX_LENGTH] = {0};
   intfstream_t* cue_stream = NULL;
   int64_t stream_size = 0;

   cue_stream = intfstream_open_file(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);

   stream_size = intfstream_get_size(cue_stream);
   cue_contents = (char*)malloc(stream_size + 1);
   if (!cue_contents)
   {
      intfstream_close(cue_stream);
      return NULL;
   }

   intfstream_read(cue_stream, cue_contents, stream_size);
   intfstream_close(cue_stream);

   cue_contents[stream_size] = '\0';

   cue = cue_contents;
   while (*cue)
   {
      cdfs_skip_spaces((const char**)&cue);
      line = cue;

      while (*cue && *cue != '\n')
         ++cue;
      if (*cue)
         *cue++ = '\0';

      if (!strncasecmp(line, "FILE", 4))
      {
         const char *file = line + 4;
         cdfs_skip_spaces(&file);

         if (file[0])
         {
            const char *file_end = cue - 1;
            while (file_end > file && *file_end != ' ' && *file_end != '\t')
               --file_end;

            if (file[0] == '"' && file_end[-1] == '"')
            {
               ++file;
               --file_end;
            }

            memcpy(current_track_path, file, file_end - file);
            current_track_path[file_end - file] = '\0';
         }
      }
      else if (!strncasecmp(line, "TRACK", 5))
      {
         unsigned track_number = 0;

         const char *track = line + 5;
         cdfs_skip_spaces(&track);

         sscanf(track, "%d", &track_number);

         if (track_index)
         {
            if (track_index == track_number)
               found_track = track_number;
         }
         else /* track_index = 0 means find the first data track */
         {
            while (track[0] && track[0] != ' ' && track[0] != '\t')
               track++;

            if (track[0])
            {
               cdfs_skip_spaces(&track);

               if (!strncasecmp(track, "MODE", 4))
                  found_track = track_number;
            }
         }
      }
      else if (found_track && !strncasecmp(line, "INDEX", 5))
      {
         const char *index = line + 5;
         cdfs_skip_spaces(&index);

         if (index[0])
         {
            unsigned index_number = 0;
            sscanf(index, "%u", &index_number);

            if (index_number == 1)
            {
               if (strstr(current_track_path, "/") || strstr(current_track_path, "\\"))
               {
                  strncpy(track_path, current_track_path, sizeof(track_path));
               }
               else
               {
                  fill_pathname_basedir(track_path, path, sizeof(track_path));
                  strlcat(track_path, current_track_path, sizeof(track_path));
               }

               break;
            }
         }
      }
   }

   free(cue_contents);

   if (string_is_empty(track_path))
      return NULL;

   return intfstream_open_file(track_path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);
}

intfstream_t* cdfs_open_track(const char* path, unsigned int track_index)
{
   const char* ext = path_get_extension(path);

   if (string_is_equal_noncase(ext, "cue"))
      return cdfs_open_cue_track(path, track_index);

   if (string_is_equal_noncase(ext, "chd"))
      return intfstream_open_chd_track(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE, track_index);

   /* unsupported file type */
   return NULL;
}

intfstream_t* cdfs_open_data_track(const char* path)
{
   const char* ext = path_get_extension(path);

   if (string_is_equal_noncase(ext, "cue"))
      return cdfs_open_cue_track(path, 0);

   if (string_is_equal_noncase(ext, "chd"))
   {
      /* TODO: determine data track */
      return intfstream_open_chd_track(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE, 1);
   }

   /* unsupported file type - try opening as a raw track */
   return cdfs_open_raw_track(path);
}

intfstream_t* cdfs_open_raw_track(const char* path)
{
   const char* ext = path_get_extension(path);

   if (string_is_equal_noncase(ext, "bin") || string_is_equal_noncase(ext, "iso"))
      return intfstream_open_file(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);

   /* unsupported file type */
   return NULL;
}
