#include <a_samp>
#include <dudb>
#include <cpstream>

#define WHITE 0xF6F6F6AA
#define GRAY 0xC6C6C6AA
#define RED 0xF60000AA
#define LIGHT_BLUE 0x00A4F6AA
#define BLUE 0x0000F6AA
#define DARK_BLUE 0x0000AFAA
#define LIGHT_GREEN 0x00F600AA
#define GREEN 0x00AD00AA
#define DARK_GREEN 0x005000AA
#define YELLOW 0xF6F600AA
#define ORANGE 0xF67F00AA

#define SERVER_COLOR 0x85F600AA
#define ERROR 0x990000AA

#define CIVILIAN 0
#define PARAMEDIC 1
#define COP 2
#define DRIVER 3
#define THIEF 4
#define HITMAN 5
#define TERRORIST 6

/*
native SendClientMessageToAdmins(const str[]);
native GetDistanceBetweenPlayers(player1, player2);
native Announce(const str[]);
native SendRadioMessageToCops(const str[]);
native SendRadioMessageToMedics(const str[]);
native SendRadioMessageToHitmen(const str[]);
native GivePlayerScore(playerid, score);
native GivePlayerWantedLevel(playerid, level);
native IsPlayerSpawned(playerid);
native GetPlayerBankCash(playerid);
native SetPlayerBankCash(playerid, cash);
native GetPlayerAdminLevel(playerid);
native SetPlayerAdminLevel(playerid, level);
native GetPlayerRobbingSkill(playerid);
native SetPlayerRobbingSkill(playerid, skill);
native GetPlayerTerrorSkill(playerid);
native SetPlayerTerrorSkill(playerid, skill);
native GetPlayerWarnings(playerid);
native SetPlayerWarnings(playerid, warns);
native SetPlayerJailed(playerid, bool);
native GetPlayerC4Amount(playerid);
native SetPlayerC4Amount(playerid, amount);
native GetPlayerDrugs(playerid);
native SetPlayerDrugs(playerid, amount);
native IsPlayerJailed(playerid);
native IsPlayerJailed(playerid);
native IsPlayerBarOwner(playerid);
*/

new RecentlyRobbed[MAX_PLAYERS];
new ATMRecentlyRobbed;
new DildoRecentlyRobbed;
new HallRecentlyRobbed;
new RentalRecentlyRobbed;
new BankRecentlyRobbed;
new BincoRecentlyRobbed;
new ZipRecentlyRobbed;
new UrbanRecentlyRobbed;
new DrugsRecentlyRobbed;

new time;

new PrisonTime[MAX_PLAYERS];
new BlowTime[MAX_PLAYERS];
new IsPlayerLogged[MAX_PLAYERS];
new ChoosingRole[MAX_PLAYERS];
new Cuffed[MAX_PLAYERS];
new HasHit[MAX_PLAYERS];
new BankRecentlyUsed[MAX_PLAYERS];
new RentedACarRecently[MAX_PLAYERS];
new InsideBar[MAX_PLAYERS];
new Working[MAX_PLAYERS];

new RobDildo[MAX_PLAYERS];
new RobHall[MAX_PLAYERS];
new RobRental[MAX_PLAYERS];
new RobBank[MAX_PLAYERS];
new RobBinco[MAX_PLAYERS];
new RobZip[MAX_PLAYERS];
new RobUrban[MAX_PLAYERS];
new RobDrugs[MAX_PLAYERS];

new PlayersOnline = 0;

// Checkpoints
new cpbankentrance, cpbankexit, cpbank;
new cpatm1, cpatm2, cpatm3, cpatm4;
new cplvpdentrance, cplvpdexit, cplvpdhand;
new cpdildoentrance, cpdildoexit, cpdildo;
new cphospital;
new cplvchentrance, cplvchexit, cpcityhall;
new cpghost;
new cpbarentrance, cpbarexit;
new cpbincoentrance, cpbincoexit, cpbinco;
new cpzipentrance, cpzipexit, cpzip;
new cpbombshop;
new cpurbanentrance, cpurbanexit, cpurban;
new cpdrugs;

// Menus
new Menu:Roles;
new Menu:Hand;
new Menu:Dildo;
new Menu:CHall;
new Menu:Rental;
new Menu:CarList;
new Menu:BarEntrance;
new Menu:Drugs;

// Objects
new bardoor, baropened = 0;
new BarStructure, barblown = 0;

// Vehicles
new BarCar;
new Rented[MAX_VEHICLES];

new Float:CivilianSpawn[][4] =
{
{2022.6539,1007.2164,10.8203,269.9900},
{2177.4451,963.9155,10.8203,359.9802},
{2362.6580,1005.0098,14.2725,91.5136},
{2435.0430,1653.7240,10.8203,178.3609},
{1947.6760,2068.7869,10.8203,89.0601},
{2346.8154,735.3505,11.4683,184.3114},
{2127.4910,2364.1289,10.8203,179.6657}
};

new Float:CopSpawn[][4] =
{
{2238.2151,2449.3613,11.0372,89.4249},
{2294.8032,2451.5522,10.8203,88.8232},
{2294.0479,2468.4722,10.8203,88.7628},
{2250.7517,2490.9146,10.9908,358.5601}
};

new Float:PrisonSpawn[][4] =
{
{198.6401,161.5331,1003.0300,181.3124},
{193.4779,175.5881,1003.0234,6.5961},
{197.7083,174.6549,1003.0234,0.0787}
};

main() print("\n	CaZeaJe's Cops and Robbers\n\n");

#pragma unused ret_memcpy

forward PlayerRecentlyRobbed();
forward HandCuffs();
forward AntiTK();
forward TimeUpdate();
forward WantedLevel();
forward Float:GetDistanceBetweenPlayers(p1, p2);
forward ShowCarListMenu(playerid);
forward Unjail();
forward RobbingDildo();
forward RobbingHall();
forward RobbingRental();
forward RobbingBank();
forward RobbingBinco();
forward RobbingZip();
forward RobbingUrban();
forward RobbingDrugs();
forward AllStores();
forward CloseBarDoor();
forward CuffedPlayers();
forward BankRecentlyUsedByRobber();
forward RecentlyRentedACar();
forward ResetParamedicWeapons();
forward BlowPlayers();
forward BlowCar(vehicleid);
forward BlowUpBar();
forward RebuildBar();
forward DriverSalary();

public DriverSalary()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(GetPlayerTeam(i) == DRIVER && Working[i] == 1)
		{
			new vehicle = GetPlayerVehicleID(i);
			for(new j = 0; j < MAX_PLAYERS; j++)
			{
				if(IsPlayerConnected(j))
				{
					if(IsPlayerInVehicle(j, vehicle) && GetPlayerState(j) == PLAYER_STATE_PASSENGER) GivePlayerMoney(i,1);
				}
			}
		}
	}
}

public RebuildBar()
{
	SetObjectPos(BarStructure, 2120.823, 1333.566, 9.820);
	barblown = 0;
	Announce("Workers have re-built BulletXT's Bar. You can now enter the Bar.");
}

public BlowUpBar()
{
	CreateExplosion(2120.823, 1333.566, 9.820+5, 6, 10);
	CreateExplosion(2120.823+3, 1333.566, 9.820, 6, 10);
	CreateExplosion(2120.823, 1333.566+3, 9.820, 6, 10);
	CreateExplosion(2120.823, 1333.566, 9.820+3, 6, 10);
	CreateExplosion(2120.823+3, 1333.566+3, 9.820+3, 6, 10);
	SetObjectPos(BarStructure, 2120.823, 1333.566, 9.820-20);
	SetTimer("RebuildBar", 300000, false);
	barblown = 1;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(InsideBar[i])
		{
			SetPlayerHealth(i, 0);
			CreateExplosion(2107.2815, 1332.8748, 1297.4639, 6, 20);
			CreateExplosion(2106.0161, 1344.2413, 1297.4639, 6, 20);
			CreateExplosion(2099.8831, 1347.6702, 1298.8623, 6, 20);
			CreateExplosion(2092.0898, 1352.2589, 1298.8623, 6, 20);
			CreateExplosion(2087.1611, 1347.0073, 1298.8623, 6, 20);
			CreateExplosion(2087.6323, 1343.8943, 1297.4639, 6, 20);
			CreateExplosion(2093.7102, 1342.5297, 1297.4639, 6, 20);
			CreateExplosion(2099.9941, 1342.5140, 1297.4639, 6, 20);
			CreateExplosion(2098.5339, 1337.9221, 1297.4639, 6, 20);
			CreateExplosion(2092.8469, 1334.8737, 1297.4639, 6, 20);
			CreateExplosion(2087.3218, 1332.4629, 1297.8623, 6, 20);
			CreateExplosion(2094.7568, 1330.1023, 1299.8936, 6, 20);
			CreateExplosion(2086.8159, 1327.3672, 1299.8936, 6, 20);
			CreateExplosion(2085.3303, 1338.6775, 1300.4795, 6, 20);
		}
	}
	Announce("BulletXT's has been blown. Workers will have to re-build it before anyone can enter.");
}

public BlowCar(vehicleid)
{
	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehicleid, x, y, z);
	CreateExplosion(x, y, z, 6, 5);
	DestroyVehicle(vehicleid);
}

public BlowPlayers()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(BlowTime[i] > 1)
			{
				BlowTime[i]--;
				new string[250], timeleft = (BlowTime[i]);
				format(string, sizeof(string), "~r~C4~w~:~n~~g~%d ~w~seconds to blow", timeleft);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(BlowTime[i] == 1)
			{
				new Float:x, Float:y, Float:z;
	            GetPlayerPos(i, x, y, z);
				CreateExplosion(x, y, z, 6, 5);
				SetPlayerHealth(i, 0);
				BlowTime[i] = 0;
			}
		}
	}
}

public ResetParamedicWeapons()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && GetPlayerTeam(i) == PARAMEDIC) ResetPlayerWeapons(i);
	}
}

public CuffedPlayers()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i) && Cuffed[i] == 1) GameTextForPlayer(i, "~w~HANDCUFFED!", 3000, 3);
	}
	return true;
}

public CloseBarDoor()
{
	MoveObject(bardoor, 2086.406, 1331.995, 1297.114, 1.5);
	baropened = 0;
}

public AllStores()
{
	if(DildoRecentlyRobbed > 0) DildoRecentlyRobbed--;
	if(ATMRecentlyRobbed > 0) ATMRecentlyRobbed--;
	if(HallRecentlyRobbed > 0) HallRecentlyRobbed--;
	if(RentalRecentlyRobbed > 0) RentalRecentlyRobbed--;
	if(BankRecentlyRobbed > 0) BankRecentlyRobbed--;
	if(BincoRecentlyRobbed > 0) BincoRecentlyRobbed--;
	if(ZipRecentlyRobbed > 0) ZipRecentlyRobbed--;
	if(UrbanRecentlyRobbed > 0) UrbanRecentlyRobbed--;
	if(DrugsRecentlyRobbed > 0) DrugsRecentlyRobbed--;
}

public RobbingDrugs()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobDrugs[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobDrugs[i]--;
				robtime = (RobDrugs[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobDrugs[i] == 1)
			{
				new earnings = random(120000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobDrugs[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed the Drug Point. Location: The Drug Point.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 9)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from the Drug Point!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingUrban()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobUrban[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobUrban[i]--;
				robtime = (RobUrban[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobUrban[i] == 1)
			{
				new earnings = random(80000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobUrban[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed SubUrban. Location: SubUrban.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 9)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from SubUrban!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingZip()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobZip[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobZip[i]--;
				robtime = (RobZip[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobZip[i] == 1)
			{
				new earnings = random(80000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobZip[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed ZIP. Location: ZIP.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 9)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from ZIP!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingBinco()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobBinco[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobBinco[i]--;
				robtime = (RobBinco[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobBinco[i] == 1)
			{
				new earnings = random(75000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobBinco[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed Binco. Location: Binco.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 9)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from Binco!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingBank()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobBank[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobBank[i]--;
				robtime = (RobBank[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobBank[i] == 1)
			{
				new earnings = random(1000000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobBank[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed CaZeaJe's Intl. Bank. Location: CaZeaJe's Intl. Bank.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 5);
				GivePlayerScore(i, 2);
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from CaZeaJe's Intl. Bank!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingRental()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobRental[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobRental[i]--;
				robtime = (RobRental[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobRental[i] == 1)
			{
				new earnings = random(75000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobRental[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed Ghost's Rental. Location: Ghost's Rental.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 29)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from Ghost's Rental!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingHall()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobHall[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobHall[i]--;
				robtime = (RobHall[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobHall[i] == 1)
			{
				new earnings = random(50000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobHall[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed the City Hall. Location: City Hall.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 9)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from the City Hall!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public RobbingDildo()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i))
		{
			if(RobDildo[i] > 1)
			{
				new string[250], robber[MAX_PLAYER_NAME], robtime;
				GetPlayerName(i, robber, sizeof(robber));
				RobDildo[i]--;
				robtime = (RobDildo[i]);
				format(string, sizeof(string), "~w~STAY IN THE CHECKPOINT~n~~g~%d~w~ SECONDS REMAINING", robtime);
				GameTextForPlayer(i, string, 3000, 3);
			}
			if(RobDildo[i] == 1)
			{
				new earnings = random(50000), robber[MAX_PLAYER_NAME], string[250], string2[250], string3[250], cops[250];
				RobDildo[i] = 0;
				GetPlayerName(i, robber, sizeof(robber));
				format(string, sizeof(string), "~w~ROBBERY COMPLETE!~n~YOU EARNED ~g~$%d", earnings);
				GameTextForPlayer(i, string, 3000, 3);
				format(cops, sizeof(cops), "[HQ] %s has robbed CaZeaJe's Dildos. Location: CaZeaJe's Dildos.", robber);
				SendRadioMessageToCops(cops);
				GivePlayerMoney(i, earnings);
				GivePlayerWantedLevel(i, 3);
				GivePlayerScore(i, 1);
				if(GetPlayerRobbingSkill(i) <= 19)
				{
					new rbskl[250];
					SetPlayerRobbingSkill(i, GetPlayerRobbingSkill(i)+1);
					format(rbskl, sizeof(rbskl), "Robbing Skill upgraded! Your skill now is: %d", GetPlayerRobbingSkill(i));
					SendClientMessage(i, SERVER_COLOR, rbskl);
				}
				SendClientMessage(i, GRAY, "|_| Crime Commited |_|");
				format(string2, sizeof(string2), "You earned $%d from CaZeaJe's Dildos!", earnings);
				SendClientMessage(i, WHITE, string2);
				format(string3, sizeof(string3), "Wanted Level: %d", GetPlayerWantedLevel(i));
				SendClientMessage(i, WHITE, string3);
			}
		}
	}
}

public Unjail()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i))
        {
			new file[256], name[MAX_PLAYER_NAME];
			GetPlayerName(i, name, sizeof(name));
			format(file, sizeof(file), "%s.czj", name);
			
            if(IsPlayerJailed(i))
            {
                if(PrisonTime[i] > 0)
                {
                    PrisonTime[i] --;
                    new string[256];
                    format(string, sizeof(string), "~w~TIME LEFT~n~~r~%d", PrisonTime[i]);
					GameTextForPlayer(i, string, 3000, 6);
                }
                if(PrisonTime[i] == 0)
                {
					new string[256];
					SetPlayerInterior(i, 3);
					SetPlayerPos(i, 231.1111, 146.7039, 1003.0234);
					SetPlayerFacingAngle(i, 272.8459);
					SetCameraBehindPlayer(i);
					SendClientMessage(i, GRAY, "|_| Las Venturas Police Dept. |_|");
					SendClientMessage(i, WHITE, "You are free to go. Just don't get into trouble.");
					format(string, sizeof(string), "%s[ID:%d] has been released from prison.", name, i);
					Announce(string);
					SetPlayerJailed(i, false);
					SetPlayerPrisonTime(i, 0);
                }
            }
        }
    }
}

public ShowCarListMenu(playerid)
{
	ShowMenuForPlayer(CarList, playerid);
}

public PlayerRecentlyRobbed()
{
	for(new i=0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && RecentlyRobbed[i] >=1)
		{
			RecentlyRobbed[i] --;
		}
	}
}

public BankRecentlyUsedByRobber()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && BankRecentlyUsed[i] >= 1)
		{
			BankRecentlyUsed[i]--;
		}
	}
}

public RecentlyRentedACar()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && RentedACarRecently[i] >= 1)
		{
			RentedACarRecently[i]--;
		}
	}
}

public AntiTK()
{
    for(new playerid; playerid < MAX_PLAYERS; playerid++)
    SetPlayerTeam(playerid, GetPlayerTeam(playerid));
    return true;
}

public TimeUpdate()
{
	if(time >= 0 && time <= 22)
	{
		new string[250], weather = random(19);
		time++;
		format(string, sizeof(string), "Time: %dh00", time);
		printf("Time: %dh00", time);
		Announce(string);
		SetWorldTime(time);
		SetWeather(weather);
	}
	else if(time == 23)
	{
		new string[250], weather = random(19);
		time = 0;
		format(string, sizeof(string), "Time: 0%dh00", time);
		printf("Time: %dh00", time);
		Announce(string);
		SetWorldTime(time);
		SetWeather(weather);
	}
}

public WantedLevel()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i) && GetPlayerWantedLevel(i) >= 1 && GetPlayerWantedLevel(i) <= 2) SetPlayerColor(i, YELLOW);
		else if(IsPlayerSpawned(i) && GetPlayerWantedLevel(i) >= 3 && GetPlayerWantedLevel(i) <= 6) SetPlayerColor(i, ORANGE);
		else if(IsPlayerSpawned(i) && GetPlayerWantedLevel(i) >= 7) SetPlayerColor(i, RED);
	}
}

public Float:GetDistanceBetweenPlayers(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2)) return -1.00;
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock GivePlayerScore(playerid, score)
{
	SetPlayerScore(playerid, GetPlayerScore(playerid)+score);
	return true;
}

stock GivePlayerWantedLevel(playerid, level)
{
	SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid)+level);
	return true;
}

stock SendClientMessageToAdmins(const str[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
		{	
	        if(GetPlayerAdminLevel(i) > 0)
			{
	            SendClientMessage(i, RED, str);
	        }
	    }
	}
	return true;
}

stock Announce(const str[])
{
	return SendClientMessageToAll(SERVER_COLOR, str);
}

stock SendRadioMessageToCops(const str[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i) && GetPlayerTeam(i) == COP) SendClientMessage(i, LIGHT_BLUE, str);
	}
	return true;
}

stock SendRadioMessageToMedics(const str[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i) && GetPlayerTeam(i) == PARAMEDIC) SendClientMessage(i, DARK_GREEN, str);
	}
	return true;
}

stock SendRadioMessageToHitmen(const str[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerSpawned(i) && GetPlayerTeam(i) == HITMAN) SendClientMessage(i, LIGHT_GREEN, str);
	}
	return true;
}

stock IsPlayerSpawned(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) return true;
	else return false;
}

stock GetPlayerBankCash(playerid)
{
	new bcash, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	bcash = dini_Int(file, "Bank");
	return bcash;
}

stock GetPlayerAdminLevel(playerid)
{
	new alevel, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	alevel = dini_Int(file, "Admin");
	return alevel;
}

stock GetPlayerRobbingSkill(playerid)
{
	new robskill, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	robskill = dini_Int(file, "RobSkill");
	return robskill;
}

stock GetPlayerTerrorSkill(playerid)
{
	new terskill, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	terskill = dini_Int(file, "TerSkill");
	return terskill;
}

stock SetPlayerBankCash(playerid, cash)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "Bank", cash);
	return true;
}

stock SetPlayerAdminLevel(playerid, level)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "Admin", level);
	return true;
}

stock SetPlayerRobbingSkill(playerid, skill)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "RobSkill", skill);
	return true;
}

stock SetPlayerTerrorSkill(playerid, skill)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "TerSkill", skill);
	return true;
}

stock GetPlayerWarnings(playerid)
{
	new warns, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	warns = dini_Int(file, "Warnings");
	return warns;
}

stock SetPlayerWarnings(playerid, warns)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "Warnings", warns);
	return true;
}

stock SetPlayerJailed(playerid, bool)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	if(bool == 1) dini_IntSet(file, "Jail", 1);
	else if(bool == 0) dini_IntSet(file, "Jail", 0);
	return true;
}

stock IsPlayerJailed(playerid)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	if(dini_Int(file, "Jail") == 1)
	{
		return true;
	}
	else if(dini_Int(file, "Jail") == 0)
	{
		return false;
	}
	return true;
}

stock GetPlayerPrisonTime(playerid)
{
	new file[256], name[MAX_PLAYER_NAME], ptime;
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	ptime = dini_Int(file, "PrisonTime");
	return ptime;
}

stock SetPlayerPrisonTime(playerid, ptime)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "PrisonTime", ptime);
	return true;
}

stock GetPlayerC4Amount(playerid)
{
	new c4s, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	c4s = dini_Int(file, "C4");
	return c4s;
}

stock SetPlayerC4Amount(playerid, amount)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "C4", amount);
	return true;
}

stock GetPlayerDrugs(playerid)
{
	new drugs, file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	drugs = dini_Int(file, "Drugs");
	return drugs;
}

stock SetPlayerDrugs(playerid, amount)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	dini_IntSet(file, "Drugs", amount);
	return true;
}

stock IsPlayerBarOwner(playerid)
{
	new file[256], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	format(file, sizeof(file), "%s.czj", name);
	if(dini_Int(file, "BarOwner") == 1)	return true;
	else if(dini_Int(file, "BarOwner") == 0) return false;
	return false;
}