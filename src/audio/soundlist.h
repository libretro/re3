﻿#pragma once

enum eSound : uint16
{
	SOUND_CAR_DOOR_CLOSE_BONNET = 0,
	SOUND_CAR_DOOR_CLOSE_BUMPER,
	SOUND_CAR_DOOR_CLOSE_FRONT_LEFT,
	SOUND_CAR_DOOR_CLOSE_FRONT_RIGHT,
	SOUND_CAR_DOOR_CLOSE_BACK_LEFT,
	SOUND_CAR_DOOR_CLOSE_BACK_RIGHT,
	SOUND_CAR_DOOR_OPEN_BONNET,
	SOUND_CAR_DOOR_OPEN_BUMPER,
	SOUND_CAR_DOOR_OPEN_FRONT_LEFT,
	SOUND_CAR_DOOR_OPEN_FRONT_RIGHT,
	SOUND_CAR_DOOR_OPEN_BACK_LEFT,
	SOUND_CAR_DOOR_OPEN_BACK_RIGHT,
	SOUND_CAR_WINDSHIELD_CRACK,
	SOUND_CAR_JUMP,
	SOUND_CAR_JUMP_2,
	SOUND_CAR_TYRE_POP,
	SOUND_16,
	SOUND_17,
	SOUND_CAR_ENGINE_START,
	SOUND_CAR_LIGHT_BREAK,
	SOUND_CAR_HYDRAULIC_1,
	SOUND_CAR_HYDRAULIC_2,
	SOUND_CAR_HYDRAULIC_3,
	SOUND_CAR_JERK,
	SOUND_CAR_SPLASH,
	SOUND_BOAT_SLOWDOWN,
	SOUND_TRAIN_DOOR_CLOSE,
	SOUND_TRAIN_DOOR_OPEN,
	SOUND_CAR_TANK_TURRET_ROTATE,
	SOUND_CAR_BOMB_TICK,
	SOUND_PLANE_ON_GROUND,
	SOUND_HELI_BLADE,
	SOUND_32,
	SOUND_STEP_START,
	SOUND_STEP_END,
	SOUND_FALL_LAND,
	SOUND_FALL_COLLAPSE,
	SOUND_FIGHT_37,
	SOUND_FIGHT_38,
	SOUND_FIGHT_39,
	SOUND_FIGHT_40,
	SOUND_FIGHT_41,
	SOUND_FIGHT_42,
	SOUND_FIGHT_43,
	SOUND_FIGHT_44,
	SOUND_FIGHT_45,
	SOUND_FIGHT_46,
	SOUND_FIGHT_47,
	SOUND_FIGHT_48,
	SOUND_49,
	SOUND_WEAPON_BAT_ATTACK,
	SOUND_WEAPON_KNIFE_ATTACK,
	SOUND_WEAPON_CHAINSAW_ATTACK,
	SOUND_WEAPON_CHAINSAW_IDLE,
	SOUND_WEAPON_CHAINSAW_MADECONTACT,
	SOUND_WEAPON_SHOT_FIRED,
	SOUND_WEAPON_RELOAD,
	SOUND_WEAPON_AK47_BULLET_ECHO,
	SOUND_WEAPON_FLAMETHROWER_FIRE,
	SOUND_WEAPON_SNIPER_SHOT_NO_ZOOM,
	SOUND_WEAPON_ROCKET_SHOT_NO_ZOOM,
	SOUND_WEAPON_HIT_PED,
	SOUND_WEAPON_HIT_VEHICLE,
	SOUND_GARAGE_NO_MONEY,
	SOUND_GARAGE_BAD_VEHICLE,
	SOUND_GARAGE_OPENING,
	SOUND_GARAGE_BOMB_ALREADY_SET,
	SOUND_GARAGE_BOMB1_SET,
	SOUND_GARAGE_BOMB2_SET,
	SOUND_GARAGE_BOMB3_SET,
	SOUND_70,
	SOUND_71,
	SOUND_GARAGE_VEHICLE_DECLINED,
	SOUND_GARAGE_VEHICLE_ACCEPTED,
	SOUND_GARAGE_DOOR_CLOSED,
	SOUND_GARAGE_DOOR_OPENED,
	SOUND_CRANE_PICKUP,
	SOUND_PICKUP_WEAPON_BOUGHT,
	SOUND_PICKUP_WEAPON,
	SOUND_PICKUP_HEALTH,
	SOUND_80,
	SOUND_81,
	SOUND_PICKUP_ADRENALINE,
	SOUND_PICKUP_ARMOUR,
	SOUND_PICKUP_BONUS,
	SOUND_PICKUP_MONEY,
	SOUND_PICKUP_HIDDEN_PACKAGE,
	SOUND_PICKUP_PACMAN_PILL,
	SOUND_PICKUP_PACMAN_PACKAGE,
	SOUND_PICKUP_FLOAT_PACKAGE,
	SOUND_BOMB_TIMED_ACTIVATED,
	SOUND_91,
	SOUND_BOMB_ONIGNITION_ACTIVATED,
	SOUND_BOMB_TICK,
	SOUND_RAMPAGE_START,
	SOUND_RAMPAGE_ONGOING,
	SOUND_RAMPAGE_PASSED,
	SOUND_RAMPAGE_FAILED,
	SOUND_RAMPAGE_KILL,
	SOUND_RAMPAGE_CAR_BLOWN,
	SOUND_EVIDENCE_PICKUP,
	SOUND_UNLOAD_GOLD,
	SOUND_PAGER,
	SOUND_PED_DEATH,
	SOUND_PED_DAMAGE,
	SOUND_PED_HIT,
	SOUND_PED_LAND,
	SOUND_PED_BULLET_HIT,
	SOUND_PED_BURNING,
	SOUND_PED_PLAYER_REACTTOCOP,
	SOUND_PED_ARREST_COP,
	SOUND_PED_MIAMIVICE_EXITING_CAR,
	SOUND_PED_COP_HELIPILOTPHRASE,
	SOUND_PED_PULLOUTWEAPON,
	SOUND_PED_HELI_PLAYER_FOUND = 114,
	SOUND_PED_VCPA_PLAYER_FOUND = 115,
	SOUND_PED_ON_FIRE,
	SOUND_PED_AIMING,
	SOUND_PED_HANDS_UP,
	SOUND_PED_HANDS_COWER,
	SOUND_PED_FLEE_SPRINT,
	SOUND_PED_CAR_JACKING,
	SOUND_PED_MUGGING,
	SOUND_PED_CAR_JACKED,
	SOUND_PED_ROBBED,
	SOUND_PED_ACCIDENTREACTION1,
	SOUND_PED_UNK_126,
	SOUND_PED_PLAYER_AFTERSEX,
	SOUND_PED_PLAYER_BEFORESEX,
	SOUND_PED_COP_UNK_129, // also used for medics
	SOUND_PED_COP_MANYCOPSAROUND, // also used for medics
	SOUND_PED_GUNAIMEDAT2,
	SOUND_PED_COP_ALONE, // also used for medics
	SOUND_PED_GUNAIMEDAT3,
	SOUND_PED_COP_REACTION,
	SOUND_PED_COP_LITTLECOPSAROUND, // also used for medics
	SOUND_PED_PLAYER_FARFROMCOPS, // also used for medics
	SOUND_PED_TAXI_WAIT,
	SOUND_PED_ATTACK,
	SOUND_PED_DEFEND,
	SOUND_PED_HEALING,
	SOUND_PED_LEAVE_VEHICLE,
	SOUND_PED_EVADE,
	SOUND_PED_FLEE_RUN,
	SOUND_PED_CRASH_VEHICLE,
	SOUND_PED_CRASH_CAR,
	SOUND_PED_ANNOYED_DRIVER,
	SOUND_PED_147,
	SOUND_PED_SOLICIT,
	SOUND_PED_149,
	SOUND_PED_150,
	SOUND_PED_EXTINGUISHING_FIRE,
	SOUND_PED_WAIT_DOUBLEBACK,
	SOUND_153,
	SOUND_PED_CHAT_SEXY,
	SOUND_PED_CHAT_EVENT,
	SOUND_PED_PED_COLLISION,
	SOUND_PED_CHAT,
	SOUND_PED_TAXI_CALL,
	SOUND_RACE_START_3,
	SOUND_RACE_START_2,
	SOUND_RACE_START_1,
	SOUND_RACE_START_GO,
	SOUND_SPLASH,
	SOUND_WATER_FALL,
	SOUND_SPLATTER,
	SOUND_CAR_PED_COLLISION,
	SOUND_CLOCK_TICK,
	SOUND_PART_MISSION_COMPLETE,
	SOUND_FRONTEND_MENU_STARTING, // same with SOUND_HUD_SOUND

	// TODO(Miami): What are 170-175??
	
	SOUND_FRONTEND_NO_RADIO = 176, // those 3 are all same sound
	SOUND_FRONTEND_RADIO_CHANGE,
	SOUND_FRONTEND_RADIO_CHANGE_2,
	SOUND_HUD_SOUND,
	SOUND_180,
	SOUND_181,
	SOUND_182,
	SOUND_LIGHTNING,
	SOUND_BULLETTRACE_1,
	SOUND_BULLETTRACE_2,
	SOUND_186, // makes same sound with 40
	SOUND_187, // makes same sound with 46
	SOUND_MELEE_ATTACK_START,
	SOUND_SKATING,
	SOUND_WEAPON_MINIGUN_ATTACK,
	SOUND_WEAPON_MINIGUN_2,
	SOUND_WEAPON_MINIGUN_3,
	SOUND_AMMUNATION_IMRAN_ARM_BOMB,
	SOUND_RADIO_CHANGE,
	SOUND_FRONTEND_HIGHLIGHT_OPTION,
	SOUND_FRONTEND_ENTER_OR_ADJUST,
	SOUND_FRONTEND_BACK,
	SOUND_FRONTEND_FAIL,
	SOUND_FRONTEND_AUDIO_TEST,
	SOUND_INJURED_PED_MALE_OUCH,
	SOUND_INJURED_PED_FEMALE,
	SOUND_SET_202,
	SOUND_SET_203,
	SOUND_TOTAL_SOUNDS = 204,
	SOUND_NO_SOUND = 205,
};


enum eScriptSounds : uint16 {
	SCRIPT_SOUND_BANK_ALARM_LOOP = 0,
	SCRIPT_SOUND_PART_MISSION_COMPLETE,
	SCRIPT_SOUND_POLICE_CELL_DOOR_SLIDING_LOOP,
	SCRIPT_SOUND_POLICE_CELL_DOOR_CLUNK,
	SCRIPT_SOUND_GARAGE_DOOR_SLIDING_LOOP,
	SCRIPT_SOUND_GARAGE_DOOR_CLUNK,
	SCRIPT_SOUND_SNORING_LOOP,
	SCRIPT_SOUND_RACE_START_3,
	SCRIPT_SOUND_RACE_START_2,
	SCRIPT_SOUND_RACE_START_1,
	SCRIPT_SOUND_RACE_START_GO,
	SCRIPT_SOUND_SHOOTING_RANGE_TARGET_MOVING_LOOP,
	SCRIPT_SOUND_SHOOTING_RANGE_TARGET_HIT,
	SCRIPT_SOUND_AMMUNATION_BUY_WEAPON,
	SCRIPT_SOUND_AMMUNATION_BUY_WEAPON_DENIED,
	SCRIPT_SOUND_WMYCW_TICKET_SPEECH,
	SCRIPT_SOUND_IMRAN_ARM_BOMB,
	SCRIPT_SOUND_ANDY_SNIPER_SHOT,
	SCRIPT_SOUND_WILLIE_CARD_SWIPE,
	SCRIPT_SOUND_MALE_AMBULANCE_OUCH,
	SCRIPT_SOUND_FEMALE_AMBULANCE_OUCH,
	SCRIPT_SOUND_BUILDING_BAR_1,
	SCRIPT_SOUND_BUILDING_BAR_2,
	SCRIPT_SOUND_BUILDING_BAR_3,
	SCRIPT_SOUND_BUILDING_BAR_4,
	SCRIPT_SOUND_BUILDING_BIKER_BAR,
	SCRIPT_SOUND_BUILDING_CHURCH,
	SCRIPT_SOUND_BUILDING_CLUB,
	SCRIPT_SOUND_BUILDING_CUBA_1,
	SCRIPT_SOUND_BUILDING_CUBA_2,
	SCRIPT_SOUND_BUILDING_VOODOO,
	SCRIPT_SOUND_BUILDING_MUSIC_SHOP,
	SCRIPT_SOUND_BUILDING_STRIPCLUB_1,
	SCRIPT_SOUND_BUILDING_STRIPCLUB_2,
	SCRIPT_SOUND_BUILDING_SUPERSWEEP,
	SCRIPT_SOUND_SEAPLANE_LOW_FUEL,
	SCRIPT_SOUND_NEW_BUILDING_BAR_1,
	SCRIPT_SOUND_NEW_BUILDING_BAR_2,
	SCRIPT_SOUND_NEW_BUILDING_BAR_3,
	SCRIPT_SOUND_NEW_BUILDING_BAR_4,
	SCRIPT_SOUND_NEW_BUILDING_MALIBU_1,
	SCRIPT_SOUND_NEW_BUILDING_MALIBU_2,
	SCRIPT_SOUND_NEW_BUILDING_MALIBU_3,
	SCRIPT_SOUND_NEW_BUILDING_STRIP_1,
	SCRIPT_SOUND_NEW_BUILDING_STRIP_2,
	SCRIPT_SOUND_NEW_BUILDING_STRIP_3,
	SCRIPT_SOUND_NEW_BUILDING_CHURCH,
	SCRIPT_SOUND_NEW_BUILDING_FAN_1,
	SCRIPT_SOUND_NEW_BUILDING_FAN_2,
	SCRIPT_SOUND_NEW_BUILDING_INSECT_1,
	SCRIPT_SOUND_NEW_BUILDING_INSECT_2,
	SCRIPT_SOUND_NEW_WATERFALL,
	SCRIPT_SOUND_BULLET_HIT_GROUND_1,
	SCRIPT_SOUND_BULLET_HIT_GROUND_2,
	SCRIPT_SOUND_BULLET_HIT_GROUND_3,
	SCRIPT_SOUND_BULLET_HIT_WATER, // no sound
	SCRIPT_SOUND_PAYPHONE_RINGING,
	SCRIPT_SOUND_GLASS_BREAK_L,
	SCRIPT_SOUND_GLASS_BREAK_S,
	SCRIPT_SOUND_GLASS_CRACK,
	SCRIPT_SOUND_GLASS_LIGHT_BREAK,
	SCRIPT_SOUND_BOX_DESTROYED_1,
	SCRIPT_SOUND_BOX_DESTROYED_2,
	SCRIPT_SOUND_METAL_COLLISION,
	SCRIPT_SOUND_TIRE_COLLISION,
	SCRIPT_SOUND_HIT_BALL,
	SCRIPT_SOUND_GUNSHELL_DROP,
	SCRIPT_SOUND_GUNSHELL_DROP_SOFT,
	SCRIPT_SOUND_TOTAL,
	SCRIPT_SOUND_INVALID,
};
