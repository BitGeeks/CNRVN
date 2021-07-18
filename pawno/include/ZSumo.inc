/*******************************************************************************
*                        ZSumo Server Include by Zuc                           *
*******************************************************************************/
#include <a_samp>
#include <dini>
#define COL_EASY           "{FFF1AF}"
#define COL_WHITE          "{FFFFFF}"
#define COL_BLACK          "{0E0101}"
#define COL_GREY           "{C3C3C3}"
#define COL_GREEN          "{6EF83C}"
#define COL_RED            "{F81414}"
#define COL_YELLOW         "{F3FF02}"
#define COL_ORANGE         "{FFAF00}"
#define COL_LIME           "{B7FF00}"
#define COL_CYAN           "{00FFEE}"
#define COL_LIGHTBLUE      "{00C0FF}"
#define COL_BLUE           "{0049FF}"
#define COL_MAGENTA        "{F300FF}"
#define COL_VIOLET         "{B700FF}"
#define COL_PINK           "{FF00EA}"
#define COL_MARONE         "{A90202}"
#define COL_CMD            "{B8FF02}"
#define COL_PARAM          "{3FCD02}"
#define COL_SERVER         "{AFE7FF}"
#define COL_VALUE          "{A3E4FF}"
#define COL_RULE           "{F9E8B7}"
#define COL_RULE2          "{FBDF89}"
#define COL_RWHITE         "{FFFFFF}"
#define COL_LGREEN         "{C9FFAB}"
#define COL_LRED           "{FFA1A1}"
#define COL_LRED2          "{C77D87}"
#define dcmd(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define ANTI_ARMOUR
#define ANTI_HEALTH
#define ANTI_VEH_HEALTH
#define ANTI_MONEY
#define ANTI_PING
#define STANDARD_TIME 12
#define STANDARD_LANGUAGE 2
#define STANDARD_GRAVITY 0.0078
#define LOW_GRAVITY 0.004
#define MAX_STREAM_OBJECTS 600
#define RING1WEATHER 1
#define RING2WEATHER 1
#define RING3WEATHER 1
#define RING4WEATHER 1
#define RING5WEATHER 1
#define RING6WEATHER 1
#define RING7WEATHER 1
#define RING8WEATHER 1
#define RING9WEATHER 1
#define RING10WEATHER 69
#define RING11WEATHER 1
#define RING12WEATHER 1
#define RING13WEATHER 1
#define STANDARD_SEC_FOR_YELLOW 100
#define STANDARD_SEC_FOR_RED 200
#define STANDARD_SEC_FOR_WIN 300
#define MAX_SERVER_PLAYERS 50
#define SCORE_ADDING 900
forward AllSpawned();
forward ScoreAdd();
forward DeleteEmptyVehicles();
forward IsUnderMinimum();
forward ScorePlayerColor();
forward RestartServer();
forward MoveRamps();
forward ShowNewRing();
forward SpawnPlayer2();
forward StartPlayer(playerid);
forward ServerConfiguration();
forward FloodTimer(playerid);
forward SpawnedPlayer(playerid);
forward CheckWin();
forward OnPlayerWinning2();
forward AntiHealthHack();
forward PlayersReCounter();
forward AntiHighPing();
forward OpeningGM();
forward NewRoundBugsCheck();
forward IsPlayerIn3DArea();
forward IsPlayerInArea(playerID, Float:minx, Float:miny, Float:maxx, Float:maxy, Float:minz, Float:maxz);
//****************************************************************************//
