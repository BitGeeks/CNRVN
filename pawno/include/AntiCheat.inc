/*
========================================================
Hey ,
Anti Cheat Include by: sKgaL
Last Update: 04/08/2013, 22:09
You can disable some Anti Cheat feature as you like. put 'false' instead of 'true'.
enjoy :)
========================================================
*/
#include <a_samp>
#include <YSI\y_hooks>

#if defined _ACheat_included
    #endinput
#endif
#define _ACheat_included

/*===============[Anti-Cheat Settings]=================*/
#define Anti_FakeKill        		true
#define Anti_SpamHack	   	true
#define Anti_CarColorHack  		true
#define Anti_CarFloatCircleHack     	true
#define Anti_JetpHack    		true
#define Anti_MoneyHack              	true
#define Anti_ArmorHack              	true
#define Anti_ConnectionsHack              	true
#define Anti_CarSpeedHack              	true
#define Anti_BotConnectionHack	true
/*=====================================================*/

/*
	public OnPlayerHack(playerid, cheatid)
	{
	    cheatid -
		1 = Chat Spam               	Hack
		2 = Fake Kill / Fast Kill 	Hack
		3 = Car Color 		Hack
		4 = Car Circle/Floating 	Hack
		5 = Jetpack                 	Hack
		6 = Money                	Hack
		7 = Armour                  	Hack
		8 = Connections		Hack
		9 = Car Speed		Hack
		10 = Bot Connection	Hack
	}
*/


enum Arr
{
	bool:DeathTimer=false,	//  Anti Fake Kill
	bool:SpammerTimer=false,    //  Anti Spammer
	bool:ColorTimer=false,      	//  Anti Car Color Hack
	bool:CarFloatTimer=false,    	//  Anti Car Circle/Floating HACK
	bool:CarSpeed=false
};
new Player[MAX_PLAYERS][Arr];	
//==============================[Defines]=======================================
	/* 	
		native SetArmour(playerid,armour);
		native GetArmour(playerid);
		native
		native GiveJetPack(playerid);
		native
	 	native GiveMoney(playerid,amount);
		native SetMoney(playerid,amount);
		native ResetMoney(playerid);
		native GetMoney(playerid);
	*/
#if Anti_ArmorHack
	#define SetArmour(%0,%1) SetPlayerArmour(%0,%1),SetPVarFloat(%0,"Armour",%1)
	#define GetArmour(%0) GetPVarFloat(playerid, "Armour")
#endif

#if Anti_JetpHack
	#define GiveJetPack(%0) SetPlayerSpecialAction(%0, SPECIAL_ACTION_USEJETPACK),SetPVarInt(%0, "Jetp",1)
#endif

#if Anti_MoneyHack
	#define GiveMoney(%0,%1) GivePlayerMoney(%0,%1),SetPVarInt(%0, "Money",GetPVarInt(%0, "Money")+%1)
	#define SetMoney(%0,%1) ResetMoney(%0), GiveMoney(%0,%1)
	#define ResetMoney(%0) ResetPlayerMoney(%0),SetPVarInt(%0, "Money",0)
	stock GetMoney(playerid)return GetPVarInt(playerid, "Money");
#endif

//==============================================================================
#if Anti_CarSpeedHack
#define HoldsTwoKeys(%0,%1) (newkeys & (%0 | %1)) == (%0| %1) && (oldkeys & (%0 | %1)) != (%0| %1)
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerInAnyVehicle(playerid) && !Player[playerid][CarSpeed])
	if(((newkeys & (KEY_FIRE)) == (KEY_FIRE)) || HoldsTwoKeys(KEY_FIRE,KEY_SPRINT) || HoldsTwoKeys(KEY_FIRE,KEY_SPRINT))
	SetTimerEx("CheckCarSpeedCheat", 1000, false, "i", playerid), Player[playerid][CarSpeed]=true;
	return 1;
}

forward CheckCarSpeedCheat(playerid);
public CheckCarSpeedCheat(playerid)
{
    new Float:x,Float:y,Float:z,Float:speed,final_speed;
    GetVehicleVelocity(GetPlayerVehicleID(playerid),x,y,z);
    speed = floatsqroot(((x*x)+(y*y))+(z*z))*100;
    final_speed = floatround(speed,floatround_round);
    Player[playerid][CarSpeed]=false;
    if(final_speed==199 ||  final_speed==200)return CallRemoteFunction("OnPlayerHack", "dd", playerid,9); // Car Speed hack	
    return 1;
}
#endif


#if Anti_ConnectionsHack
new DetectIP[16], IPConnectionCount=0;
new bool:ConnectionTimerClear;
#endif
hook OnPlayerConnect(playerid)
{
	SendClientMessage(playerid,-1,"{C0C0C0}This server is protected by {FF0000}'sK'{C0C0C0} Anti Cheat.");
	#if Anti_ConnectionsHack
	new ppIP[16];
	GetPlayerIp(playerid, ppIP, sizeof(ppIP));
	if(strcmp(DetectIP, ppIP)!=0)strdel(DetectIP, 0, sizeof(DetectIP)),strcat(DetectIP,ppIP),IPConnectionCount=0;
	else if(!strcmp(DetectIP, ppIP))
	{
		if(!ConnectionTimerClear)SetTimer("ConnectionTimer", 1000, false),ConnectionTimerClear=true;
		IPConnectionCount++;
		if(IPConnectionCount==2)
		{
			if(!IsPlayerNPC(playerid))return CallRemoteFunction("OnPlayerHack", "dd", playerid,8); // Connection hack
			#if Anti_BotConnectionHack
			else
			{
				new pip[16];
				for(new i=0,j=GetMaxPlayers();i<j;i++)if(IsPlayerConnected(i))
				{
					GetPlayerIp(i, pip, sizeof(pip));
					if(!strcmp(ppIP, pip, true))
					{
						if(IsPlayerNPC(i)) Kick(i);
						else CallRemoteFunction("OnPlayerHack", "dd", playerid,10);// Bot Connection hack
					}	
				}
			}
			#endif
		}	
	}
	#endif
	return 1;
}
#if Anti_ConnectionsHack
public ConnectionTimer() ConnectionTimerClear=false, IPConnectionCount=0, strdel(DetectIP, 0, sizeof(DetectIP));
#endif

hook OnPlayerUpdate(playerid)
{
	#if Anti_JetpHack
	    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && GetPVarInt(playerid, "Jetp")==0)return CallRemoteFunction("OnPlayerHack", "dd", playerid,5);// Jetpack hack
	    else if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK && GetPVarInt(playerid, "Jetp")==1)return DeletePVar(playerid,"Jetp");
	#endif

    #if Anti_MoneyHack
		if(GetPlayerMoney(playerid)>GetPVarInt(playerid, "Money"))return CallRemoteFunction("OnPlayerHack", "dd", playerid,6);// Money hack
		else if(GetPlayerMoney(playerid)==GetPVarInt(playerid, "Money")-1)SetPVarInt(playerid, "Money",GetPVarInt(playerid, "Money")-1);
    #endif
    
    #if Anti_ArmorHack
	new Float:armour;
	GetPlayerArmour(playerid, armour);
	if(GetPVarInt(playerid, "UsedPick")==1)return DeletePVar(playerid,"UsedPick"),SetPVarFloat(playerid, "Armour",armour);
	if(armour>GetPVarFloat(playerid, "Armour"))return CallRemoteFunction("OnPlayerHack", "dd", playerid,7);// Armour hack
    #endif
    return 1;
}

hook OnPlayerText(playerid, text[])
{
	#if Anti_SpamHack
		if(!Player[playerid][SpammerTimer])SetTimerEx("SpamOK",100,false,"i",playerid),Player[playerid][SpammerTimer]=true;
		else if(Player[playerid][SpammerTimer])
		{
			SetPVarInt(playerid, "Spam", GetPVarInt(playerid, "Spam")+1);
	    	if(GetPVarInt(playerid, "Spam")==12)return CallRemoteFunction("OnPlayerHack", "dd", playerid,1); // Spam hack
		}
	#endif
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    SendDeathMessage(killerid, playerid, reason); 
	#if Anti_FakeKill
	    if(killerid==playerid)
	    {
	        switch(reason)
	        {
	            case 0..47:return CallRemoteFunction("OnPlayerHack", "dd", playerid,2); // Fake Kill Hack
	            case 255:return CallRemoteFunction("OnPlayerHack", "dd", playerid,2);   // Fake Kill Hack
	        }
	    }

		if(!Player[playerid][DeathTimer])SetTimerEx("DeathOK",200,false,"i",playerid),Player[playerid][DeathTimer]=true;
		else if(Player[playerid][DeathTimer])
		{
			SetPVarInt(playerid, "Death", GetPVarInt(playerid, "Death")+1);
	        if(GetPVarInt(playerid, "Death")==5)return CallRemoteFunction("OnPlayerHack", "dd", playerid,2); // Fake Kill Hack
		}
	#endif
    return 1;
}

hook OnVehicleRespray(playerid, vehicleid, color1, color2)
{
#if Anti_CarColorHack
if(!Player[playerid][ColorTimer])SetTimerEx("ColorOK",500,false,"i",playerid),Player[playerid][ColorTimer]=true;
else if(Player[playerid][ColorTimer])
{
	SetPVarInt(playerid, "Color", GetPVarInt(playerid, "Color")+1);
	if(GetPVarInt(playerid, "Color")==20)return CallRemoteFunction("OnPlayerHack", "dd", playerid,3); // Vehicle Color Hack
}
#endif
return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	#if Anti_CarFloatCircleHack
	    if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
	    {
			if(!Player[playerid][CarFloatTimer])SetTimerEx("CarOK",400,false,"i",playerid),Player[playerid][CarFloatTimer]=true;
			else if(Player[playerid][CarFloatTimer])
			{
				SetPVarInt(playerid, "CarFloat", GetPVarInt(playerid, "CarFloat")+1);
			    if(GetPVarInt(playerid, "CarFloat")==5)CallRemoteFunction("OnPlayerHack", "dd", playerid,4); // Car Float/Circle HACK
			}
		}
	#endif
   	return 1;
}

hook OnPlayerPickUpPickup(playerid, pickupid)
{
    if(pickupid==1242)SetPVarInt(playerid, "UsedPick",1);
    return 1;
}

forward DeathOK(playerid);
forward ColorOK(playerid);
forward CarOK(playerid);
forward SpamOK(playerid);
forward OnPlayerHack(playerid, cheatid);
forward ConnectionTimer();

public DeathOK(playerid) DeletePVar(playerid,"Death"),Player[playerid][DeathTimer]=false; // Anti Fake Kill
public ColorOK(playerid) DeletePVar(playerid,"Color"),Player[playerid][ColorTimer]=false; // Anti Vehicle Color Hack
public CarOK(playerid)   DeletePVar(playerid,"CarFloat"),Player[playerid][CarFloatTimer]=false; // Anti Vehicle Float/Circle Hack
public SpamOK(playerid)  DeletePVar(playerid,"Spam"),Player[playerid][SpammerTimer]=false; // Anti Spammer
