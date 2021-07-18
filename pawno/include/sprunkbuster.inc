#include <a_samp>
#include <a_http>
#include "nex-ac.inc"

#define JSON_TARGET_CHECK          "abstractiondev.net/sprunkbuster/sa/check.php?serial=%s&ip=%s" // done

native gpci(playerid,serial[],len);
/*
JSON FUNCTIONS REFERENCE
native JSONNode:json_parse_string(const string[]);
native json_close(JSONNode:node);
native bool:json_get_bool(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER);
native json_get_int(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER);
native json_get_string(JSONNode:node, dst[], const len = sizeof(dst), const path[] = '\0', const bool:packed = false, const path_delim = JSON_DEFAULT_DELIMITER);
*/

// Sprunkbuster Include Functions
forward SB_OnPlayerConnect(playerid);
forward SB_ExemptPlayer(playerid,exemption_state); // 1 for exempt, 0 for not-exempt (primitive whitelisting)
forward SB_ProcessConnection(index, response_code, data[]);
forward SB_Enable();
forward SB_Disable();

// Nex-AC Functions (Credits to Nexius for Nex-AC)
forward OnCheatDetected(playerid, ip_address[], type, code);

new ViolationTimer;
forward DecreaseViolation();

enum E_VIOLATION_INFO
{
	ViolationCount,
	LastViolation,
}
new Violations[MAX_PLAYERS][E_VIOLATION_INFO];
new CheatExemption[MAX_PLAYERS];

SB_BanPlayer(playerid,code)
{
    if(Violations[playerid][ViolationCount] >= 240)
   	{
		Violations[playerid][ViolationCount] = 0;
		Violations[playerid][LastViolation] = 0;

		CallRemoteFunction("SB_ProcessBan","ii",playerid,code);
	}
}
SB_LogCheatAttempt(playerid,code)
{
    if(Violations[playerid][ViolationCount] < 300)
    {
		CallRemoteFunction("SB_ProcessEvent","ii",playerid,code);
	}
}
public SB_Enable()
{
	// Resets the tracking data in case of filterscript reload
	for(new playerid = 0; playerid <= GetPlayerPoolSize(); playerid++)
	{
	    Violations[playerid][ViolationCount] = 0;
		Violations[playerid][LastViolation] = 0;
		CheatExemption[playerid] = 0;
	}
	
	ViolationTimer = SetTimer("DecreaseViolation",2000,true);
}
public SB_Disable()
{
    KillTimer(ViolationTimer);
}
public SB_OnPlayerConnect(playerid)
{
    new serial[128];
	new ipaddr[16];

	Violations[playerid][ViolationCount] = 0;
	Violations[playerid][LastViolation] = 0;
	CheatExemption[playerid] = 0;

	gpci(playerid,serial,128);
	GetPlayerIp(playerid,ipaddr,16);

	new http_request[256];
	format(http_request,256,JSON_TARGET_CHECK,serial,ipaddr);
	// printf("%s",http_request); // Debug
	HTTP(playerid,HTTP_GET,http_request,"","SB_ProcessConnection");

	printf("[Sprunkbuster] Querying Sprunkbuster SA for global bans...");
	printf("[Sprunkbuster] Request: Sending query for SAMP Serial '%s'",serial);
	printf("[Sprunkbuster] Request: Sending query for IP Address '%s'",ipaddr);
}
public SB_ProcessConnection(index, response_code, data[])
{
	CallRemoteFunction("SB_OnStatusChecked","iis",index,response_code,data);
}

// Nex AC Functions
public OnCheatDetected(playerid, ip_address[], type, code)
{
	if(!CheatExemption[playerid])
	{
	    if((gettime() - Violations[playerid][LastViolation]) > 10)
	    { // At least 10 seconds have passed since the last attempt to cheat (ensures this is a separate event)
	        printf("[Sprunkbuster] Detected ID %d as a possible cheater.",playerid); // Removed info about the code to counter reverse engineering
			Violations[playerid][ViolationCount] = Violations[playerid][ViolationCount] + 100; // 100 warning points
			Violations[playerid][LastViolation] = gettime();

			if(Violations[playerid][ViolationCount] >= 240)
			{
			    SB_LogCheatAttempt(playerid,code);
				SB_BanPlayer(playerid,code); // sends data about the attempt to sprunkbuster, and bans the player
			}
			else SB_LogCheatAttempt(playerid,code); // sends data about the attempt to Sprunkbuster
		}
	}
	
	CallRemoteFunction("SB_OnCheatDetected","isii",playerid,ip_address,type,code);
}
public DecreaseViolation()
{
	for(new playerid = 0; playerid <= GetPlayerPoolSize(); playerid++)
	{
	    if(IsPlayerConnected(playerid))
	    {
	        if(Violations[playerid][ViolationCount] > 300)
	        {
	            if((gettime() - Violations[playerid][LastViolation]) > 60)
	            { // At least 60 seconds have passed since the cheating attempt, decrease violation level (else do not decrement)
	                Violations[playerid][ViolationCount]--;
	            }
	        }
	    }
	}
}
public SB_ExemptPlayer(playerid,exemption_state)
{
	CheatExemption[playerid] = exemption_state;
	if(exemption_state) printf("[Sprunkbuster] Player ID %d is now exempt from Sprunkbuster bans on your server.",playerid);
	else                printf("[Sprunkbuster] Player ID %d is no longer exempt from Sprunkbuster bans on your server.",playerid);
	return 1;
}
