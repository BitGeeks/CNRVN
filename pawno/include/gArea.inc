/*
	gArea by Gamer931215 V1.1b
	Credits to Donya for the "OnPlayerLeaveArea idea"
	Free to use (do NOT sell/mirror/clame it as your own/merge it with any other script)

	Native defines (for autofill functionality in pawno using my functions)
	    native CreateArea(Float:x,Float:y,Float:range)
	    native CreateAreaEx(Float:minx,Float:miny,Float:maxx,Float:maxy)
	    native OnPlayerEnterArea(playerid,areaid)
	    native ToggleArea(areaid,bool:toggle)
*/

/*===============================================
|			  Settings/Initialising             |
================================================*/

#if !defined MAX_AREAS
	#define MAX_AREAS			10
#endif
#if !defined TIMER_TICKRATE
	#define TIMER_TICKRATE      1000
#endif

#if defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
		SetTimer("scan_players",TIMER_TICKRATE,true);
		return CallLocalFunction("gArea_OnFilterScriptInit","");
	}
	#if defined _ALS_OnFilterScriptInit
	    #undef OnFilterScriptInit
	#else
	    #define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit gArea_OnFilterScriptInit
	forward gArea_OnFilterScriptInit();
#else
	public OnGameModeInit()
	{
	    SetTimer("scan_players",TIMER_TICKRATE,true);
	    return CallLocalFunction("gArea_OnGameModeInit","");
	}
	#if defined _ALS_OnGameModeInit
	    #undef OnGameModeInit
	#else
	    #define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit gArea_OnGameModeInit
	forward gArea_OnGameModeInit();
#endif

/*===============================================
|           	Internal Variables              |
================================================*/
enum area
{
	Float:_minx,
	Float:_miny,
	Float:_maxx,
	Float:_maxy,
	bool:_used,
	bool:_userangeofpoint,
	bool:_active
}
new areas[MAX_AREAS][area];
forward OnPlayerEnterArea(playerid,areaid);
forward OnPlayerLeaveArea(playerid,areaid);

/*===============================================
|           	External functions              |
================================================*/
stock CreateArea(Float:x,Float:y,Float:range)
{
	new id = GenerateID();
	if(id == -1) return print("Error! gArea's maximum arealimit has been reached!");
	areas[id][_minx] = x;
	areas[id][_miny] = y;
	areas[id][_maxx] = range;
	areas[id][_userangeofpoint] = true;
	areas[id][_used] = true;
	areas[id][_active] = true;
	return id;
}
stock CreateAreaEx(Float:minx,Float:miny,Float:maxx,Float:maxy)
{
	new id = GenerateID();
	if(id == -1) return print("Error! gArea's maximum arealimit has been reached!");
	areas[id][_minx] = minx;
	areas[id][_miny] = miny;
	areas[id][_maxx] = maxx;
	areas[id][_maxy] = maxy;
	areas[id][_used] = true;
	areas[id][_userangeofpoint] = false;
	areas[id][_active] = true;
	return id;
}

stock ToggleArea(areaid,bool:toggle)
{
	if(toggle == true)
	{
	    areas[areaid][_active] = true;
	} else {
	    areas[areaid][_active] = false;
	}
	return 1;
}

/*===============================================
|           	Internal functions              |
================================================*/

public OnPlayerDisconnect(playerid, reason)
{
	return CallLocalFunction("gArea_OnPlayerDisconnect","ii",playerid,reason);
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define gArea_OnPlayerDisconnect OnPlayerDisconnect
forward gArea_OnPlayerDisconnect(playerid,reason);

stock GenerateID()
{
	for(new i = 0;i<MAX_AREAS;i++)
	{
	    if(areas[i][_used] == false) return i;
	}
	return -1;
}

stock IsPlayerInArea(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy)
{
    new Float:x, Float:y, Float:z;GetPlayerPos(playerid, x, y, z);
    if (x > minx && x < maxx && y > miny && y < maxy) return 1;
    return 0;
}

forward scan_players();
public scan_players()
{
	for(new a = 0;a<MAX_PLAYERS;a++)
	{
	    for(new b = 0;b<MAX_AREAS;b++)
	    {
	        if(areas[b][_active] == true)
	        {
	            if(areas[b][_userangeofpoint] == false) //use with IsPlayerInRangeOfPoint
	            {
	                if(IsPlayerInArea(a,areas[b][_minx],areas[b][_maxx],areas[b][_miny],areas[b][_maxy]))
	                {
	                    if((GetPVarInt(a,"gArea_entered") -1) != b)
	                    {
		                    SetPVarInt(a,"gArea_entered",(b +1));
		                    OnPlayerEnterArea(a,(b));
	                    }
	                } else {
	                    if(GetPVarInt(a,"gArea_entered"))
	                    {
	                        if((GetPVarInt(a,"gArea_entered") -1) == b)
	                        {
		                        OnPlayerLeaveArea(a,(GetPVarInt(a,"gArea_entered") -1));
		                        DeletePVar(a,"gArea_entered");
							}
	                    }
	                }
	            } else { //use with IsPlayerInRangeOfPoint()
					new Float:z;GetPlayerPos(a,z,z,z);
	                if(IsPlayerInRangeOfPoint(a,areas[b][_maxx],areas[b][_minx],areas[b][_miny],z))
	                {
	                    if((GetPVarInt(a,"gArea_entered") -1) != b)
	                    {
		                    SetPVarInt(a,"gArea_entered",(b +1));
		                    OnPlayerEnterArea(a,(b));
	                    }
	                } else {
	                    if(GetPVarInt(a,"gArea_entered"))
	                    {
	                        if((GetPVarInt(a,"gArea_entered") -1) == b)
	                        {
		                        OnPlayerLeaveArea(a,(GetPVarInt(a,"gArea_entered") -1));
		                        DeletePVar(a,"gArea_entered");
							}
	                    }
	                }
	            }
	        }
	    }
	}
	return 1;
}