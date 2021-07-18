enum FGPS
{
	ID,
	Float: LocationX,
	Float: LocationY,
	Float: LocationZ,
	PlaceName[128]
};
new GPSInfo[MAX_LOCATIONS][FGPS];
new DB:GPSDB;
new GPSObject[MAX_PLAYERS];
new gValue[128];

stock GetPlayerLocationFromId(playerid, id)
{
	new
		Query[128],
		DBResult:qresult,
		string[128],
		string2[128],
		NameStore[128]
	;

	format(Query, sizeof(Query), "SELECT `LocationX`, `LocationY`, `LocationZ`, `Name` FROM `FGPSSystem` WHERE ID = '%d'", id);
	qresult = db_query(GPSDB, Query);

	db_get_field_assoc(qresult, "LocationX", string,128);		SetPVarFloat(playerid, "Spongebob", floatstr(string));
	db_get_field_assoc(qresult, "LocationY", string,128);		SetPVarFloat(playerid, "Mario", floatstr(string));
	db_get_field_assoc(qresult, "LocationZ", string,128);		SetPVarFloat(playerid, "SpiderPig", floatstr(string));
	db_get_field_assoc(qresult, "Name", string,128);			SetPVarString(playerid, "FAIL", string);

	GetPVarString(playerid, "FAIL", NameStore, 128);
	format(string2,sizeof(string2),"Follow the arrow to reach "CHAT_YELLOW"%s", NameStore);

	Server(playerid, string2);

 	GPSObject[playerid] = CreateObject(1318, 0, 0, 0, 0.0, 0.0, 0);
  	SetPVarInt(playerid, "YEAH", 1);
	db_free_result(qresult);

	return 1;
}

stock ReloadDatabase()
{
    new DBResult:qresult, count = 0, value[128];
	qresult = db_query(GPSDB, "SELECT * FROM `FGPSSystem`");
	count = db_num_rows(qresult);
	for(new a=0;a<count;a++)
	{
		if(count >= 1 && count <= MAX_LOCATIONS)
		{
 			db_get_field_assoc(qresult, "ID", value, 5);	 			GPSInfo[a][ID] = strval(value);
			db_get_field_assoc(qresult, "LocationX", value, 20);	 	GPSInfo[a][LocationX] = floatstr(value);
			db_get_field_assoc(qresult, "LocationY", value, 20);	 	GPSInfo[a][LocationY] = floatstr(value);
			db_get_field_assoc(qresult, "LocationZ", value, 20); 	 	GPSInfo[a][LocationZ] = floatstr(value);
			db_get_field(qresult,4,value,128);                          strmid(GPSInfo[a][PlaceName], value, 0, strlen(value), 128);
			db_next_row(qresult);
		}
	}
	db_free_result(qresult);
	return 1;
}

stock GetLastID()
{
    new DBResult:qresult, count = 0, Value[128];
	qresult = db_query(GPSDB, "SELECT * FROM `FGPSSystem` ORDER BY `ID` DESC LIMIT 1");
	count = db_num_rows(qresult);

	for(new a=0;a<count;a++)
	{
		if(count <= MAX_LOCATIONS)
		{
 			db_get_field_assoc(qresult, "ID", Value, 5);	gValue[a] = Value[a]+1;
			db_next_row(qresult);
		}
	}

	db_free_result(qresult);
	return 1;
}

stock LoadFGPS()
{
	new query[256], DBResult:qresult, count = 0, value[128];
	if(!db_query(DB: GPSDB, "SELECT * FROM `FGPSSystem`"))
	{
		print("Таблица не найдена... Создание таблицы!");
		format(query,sizeof(query),"CREATE TABLE IF NOT EXISTS `FGPSSystem` (`ID`, `LocationX`, `LocationY`, `LocationZ`, `Name`)");
	 	db_query(GPSDB,query);
		print("GPS System Loaded...");
		print("--------------------------------------\n");
		SendRconCommand("exit");
	}
	else
	{
		qresult = db_query(GPSDB,  "SELECT * FROM `FGPSSystem`");
		count = db_num_rows(qresult);
		for(new a=0;a<count;a++)
		{
			if(count >= 1 && count <= MAX_LOCATIONS)
			{
		    	db_get_field_assoc(qresult, "ID", value, 5);	 			GPSInfo[a][ID] = strval(value);
				db_get_field_assoc(qresult, "LocationX", value, 20);	 	GPSInfo[a][LocationX] = floatstr(value);
				db_get_field_assoc(qresult, "LocationY", value, 20);	 	GPSInfo[a][LocationY] = floatstr(value);
				db_get_field_assoc(qresult, "LocationZ", value, 20); 	 	GPSInfo[a][LocationZ] = floatstr(value);
				db_get_field(qresult,4,value,128);                          strmid(GPSInfo[a][PlaceName], value, 0, strlen(value), 128);
				printf("%d, %f, %f, %f, %s", GPSInfo[a][ID],GPSInfo[a][LocationX],GPSInfo[a][LocationY],GPSInfo[a][LocationZ],GPSInfo[a][PlaceName]);
				db_next_row(qresult);
			}
		}
		db_free_result(qresult);
		print("GPS System Loaded...");
		print("--------------------------------------\n");
	}
	return 1;
}

stock disableGPS(playerid)
{
	if(GetPVarInt(playerid,"YEAH") == 1)
	{
   		DestroyObject(GPSObject[playerid]);
   		SetPVarInt(playerid, "YEAH",0);
   		DeletePVar(playerid, "Spongebob");
   		DeletePVar(playerid, "Mario");
   		DeletePVar(playerid, "SpiderPig");
   		DeletePVar(playerid, "FAIL");
	}
	return 1;
}

COMMAND:gps(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
	{
		Server(playerid, "You must be in a vehicle to use the gps.");
		return 1;
	}
    if(GetPVarInt(playerid,"YEAH") == 1)
	{
		Server(playerid, "Use /turnoff to disable your current route.");
		return 1;
	}
	new string[128], var[2048];
	for(new g = 0; g < sizeof(GPSInfo); g++)
 	{
 		format(string, 128, "%s\n", GPSInfo[g][PlaceName]);
 		strcat(var,string);
 	}
	if(!strlen(GPSInfo[0][PlaceName]))
	{
		Server(playerid, "There's no locations available.");
		return 1;
	}
 	ShowPlayerDialog(playerid, DIALOG_GPS, DIALOG_STYLE_LIST, "Find Location", var, "Turn on", "Close");
	return 1;
}

COMMAND:turnoff(playerid, params[])
{
    if(GetPVarInt(playerid, "YEAH") == 0)
    {
		Server(playerid, "Your GPS is not enabled.");
		return 1;
	}
   	DestroyObject(GPSObject[playerid]);
   	SetPVarInt(playerid, "YEAH", 0);
   	DeletePVar(playerid, "Spongebob");
   	DeletePVar(playerid, "Mario");
   	DeletePVar(playerid, "SpiderPig");
   	DeletePVar(playerid, "FAIL");
	Server(playerid, "Your GPS is now disabled!.");
	return 1;
}

COMMAND:fsave(playerid, params[])
{
    if(!IsPlayerAdmin(playerid)) 
		return 0;
	
	new Float:PPos[3], string[128], query[256];
  	GetPlayerPos(playerid, PPos[0], PPos[1], PPos[2]);
    if(!strlen(params))
	{	
		Usage(playerid, "fsave <name>");
		return 1;
	}
    GetLastID();
   	new NewID = strval(gValue);
	format(query, sizeof(query), "INSERT INTO `FGPSSystem` (`ID`,`LocationX`,`LocationY`,`LocationZ`, `Name`) VALUES('%d','%f','%f','%f','%s');",NewID,PPos[0],PPos[1],PPos[2],params);
	db_query(GPSDB,query);
	ReloadDatabase();
	format(string,sizeof(string),"You have set: "CHAT_YELLOW"%s's{FFFFFF} location in the GPS.", params);
	Server(playerid, string);
	return 1;
}

COMMAND:fedit(playerid, params[])
{
    if(!IsPlayerAdmin(playerid))
		return 0;

	new string[128], query[256], tmp[2][128];
    if(sscanf(params, "s[128]s[128]", tmp[1], tmp[0]))
	{
		Usage(playerid, "fedit <old location> <new location>");
	}
	else
	{
		format(query, sizeof(query), "UPDATE `FGPSSystem` SET `Name` = '%s' WHERE `Name` = '%s'",tmp[1],tmp[0]);
		db_query(GPSDB,query);
		ReloadDatabase();
		format(string,sizeof(string),"You have edited: "CHAT_YELLOW"%s {FFFFFF}to "CHAT_YELLOW"%s", tmp[0],tmp[1]);
		Server(playerid, string);
	}
	return 1;
}
