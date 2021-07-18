/********************************************************** pEscapemenu v1.0 ***
*
* Scriptname:
* -» pEscapemenu
*
* Author:
* -» Pablo_Borsellino
*
* Creation Date:
* -» 18th October 2011
*
* Release Date:
* -» 19th October 2011
*
* Changelog:
* • v1.0 (19.10.2011)
* -» Initial Release
*
* Need to use:
* -» nothing special
*
* Language:
* -» English
*
* Description:
* -» Some Functions to create a Menu like Escape Menu with some dynamic things.
*
* Functions:
* -» OnEscapeMenuInit()
* -» OnEscapeMenuExit()
* -» OnEscapeMenuKeyStateChange(playerid,newkeys);
* -» OnEscapeMenuUpdate(playerid);
* -» OnEscapeMenuDisconnect(playerid);
* -» OnEscapeMenuConnect(playerid);
*
* -» ShowPlayerEscapeMenu(playerid,Title[],Option1[],Option2[],Option3[],Option4[],Option5[],Option6[],Option7[]);
* -» HidePlayerEscapeMenu(playerid);
* -» SetPlayerEscapeMenuOptionText(playerid,OptionID,NewText[]);
* -» RemovePlayerEscapeMenuOption(playerid,OptionID)
*
* If-Queries:
* -» EscapeMenuOpen(playerid)
* -» IsValidEscapeMenuOption(playerid,OptionID)
*
* Public's:
* -» OnPlayerEscapeMenuRowChange(playerid,NewRowID)
* -» OnPlayerEscapeMenuResponse(playerid,SelectedRow)
*
* Credit's:
* -» n/a
*											Copyright © 2011 by Pablo_Borsellino
*******************************************************************************/
//__________________________________________________________________Definition's
#define forEx(%0,%1) for(new %1=0;%1<%0;%1++)

//_____________________________________________________________________Setting's
#define ESC_SWITCH_SOUND 1056       //Sound that got played if switch Up/Down
#define ESC_MOVE_TIME_DISTANCE 222	//Distance in Milliseconds between Moving
#define ESC_KEY_TO_RESPONSE KEY_SECONDARY_ATTACK   //Key to response the Menu

//_____________________________________________________________________Forward's
forward OnPlayerEscapeMenuRowChange(playerid,NewRowID);
forward OnPlayerEscapeMenuResponse(playerid,SelectedRow);

//____________________________________________________________________Variable's
new Text:TD_ESC_Menu_Opt_1,
	Text:TD_ESC_Menu_Opt_2,
	Text:TD_ESC_Menu_Opt_3,
	Text:TD_ESC_Menu_Opt_4,
	Text:TD_ESC_Menu_Opt_5,
	Text:TD_ESC_Menu_Opt_6,
	Text:TD_ESC_Menu_Opt_7,
	Text:TD_ESC_Menu_Title,
	Text:TD_ESC_Menu_Backg,
	_ESC_PLAYER_ROW_POSITION[MAX_PLAYERS]=0,
	bool:_ESC_PLAYER_MOVE[MAX_PLAYERS]=true,
	bool:_ESC_PLAYER_SEE_MENU[MAX_PLAYERS]=false,
	bool:_ESC_PLAYER_FUNC_AVAILABLE[MAX_PLAYERS][7];

//______________________________________________________________________Public's
OnEscapeMenuInit()
{
	TD_ESC_Menu_Backg=TextDrawCreate(0,0,"Hintergrund");
	TextDrawBackgroundColor(TD_ESC_Menu_Backg,255);
	TextDrawFont(TD_ESC_Menu_Backg,1);
	TextDrawLetterSize(TD_ESC_Menu_Backg,0,51);
	TextDrawColor(TD_ESC_Menu_Backg,-1);
	TextDrawSetOutline(TD_ESC_Menu_Backg,0);
	TextDrawSetProportional(TD_ESC_Menu_Backg,1);
	TextDrawSetShadow(TD_ESC_Menu_Backg,1);
	TextDrawUseBox(TD_ESC_Menu_Backg,1);
	TextDrawBoxColor(TD_ESC_Menu_Backg,255);
	TextDrawTextSize(TD_ESC_Menu_Backg,640,00);

	TD_ESC_Menu_Opt_1=TextDrawCreate(319,140,"Forsetzen");
	TextDrawAlignment(TD_ESC_Menu_Opt_1,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_1,255);
	TextDrawFont(TD_ESC_Menu_Opt_1,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_1,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_1,-823266817);
	TextDrawSetOutline(TD_ESC_Menu_Opt_1,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_1,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_1,0);

	TD_ESC_Menu_Opt_2=TextDrawCreate(319,170,"Neues Spiel Starten");
	TextDrawAlignment(TD_ESC_Menu_Opt_2,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_2,255);
	TextDrawFont(TD_ESC_Menu_Opt_2,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_2,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_2,1786416127);
	TextDrawSetOutline(TD_ESC_Menu_Opt_2,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_2,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_2,0);

	TD_ESC_Menu_Opt_3=TextDrawCreate(319,200,"Karte");
	TextDrawAlignment(TD_ESC_Menu_Opt_3,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_3,255);
	TextDrawFont(TD_ESC_Menu_Opt_3,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_3,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_3,1786416127);
	TextDrawSetOutline(TD_ESC_Menu_Opt_3,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_3,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_3,0);

	TD_ESC_Menu_Opt_4=TextDrawCreate(319,230,"Statistik");
	TextDrawAlignment(TD_ESC_Menu_Opt_4,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_4,255);
	TextDrawFont(TD_ESC_Menu_Opt_4,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_4,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_4,1786416127);
	TextDrawSetOutline(TD_ESC_Menu_Opt_4,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_4,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_4,0);

	TD_ESC_Menu_Opt_5=TextDrawCreate(319,260,"Info");
	TextDrawAlignment(TD_ESC_Menu_Opt_5,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_5,255);
	TextDrawFont(TD_ESC_Menu_Opt_5,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_5,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_5,1786416127);
	TextDrawSetOutline(TD_ESC_Menu_Opt_5,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_5,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_5,0);

	TD_ESC_Menu_Opt_6=TextDrawCreate(319,291,"Optionen");
	TextDrawAlignment(TD_ESC_Menu_Opt_6,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_6,255);
	TextDrawFont(TD_ESC_Menu_Opt_6,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_6,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_6,1786416127);
	TextDrawSetOutline(TD_ESC_Menu_Opt_6,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_6,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_6,0);

	TD_ESC_Menu_Opt_7=TextDrawCreate(319,320,"Spiel beenden");
	TextDrawAlignment(TD_ESC_Menu_Opt_7,2);
	TextDrawBackgroundColor(TD_ESC_Menu_Opt_7,255);
	TextDrawFont(TD_ESC_Menu_Opt_7,2);
	TextDrawLetterSize(TD_ESC_Menu_Opt_7,0.75,1.9);
	TextDrawColor(TD_ESC_Menu_Opt_7,1786416127);
	TextDrawSetOutline(TD_ESC_Menu_Opt_7,0);
	TextDrawSetProportional(TD_ESC_Menu_Opt_7,1);
	TextDrawSetShadow(TD_ESC_Menu_Opt_7,0);

	TD_ESC_Menu_Title=TextDrawCreate(40,28,"Pausenmenu");
	TextDrawBackgroundColor(TD_ESC_Menu_Title,255);
	TextDrawFont(TD_ESC_Menu_Title,0);
	TextDrawLetterSize(TD_ESC_Menu_Title,1.38,4.2);
	TextDrawColor(TD_ESC_Menu_Title,-823266817);
	TextDrawSetOutline(TD_ESC_Menu_Title,0);
	TextDrawSetProportional(TD_ESC_Menu_Title,1);
	TextDrawSetShadow(TD_ESC_Menu_Title,1);

	forEx(MAX_PLAYERS,playerid)
		_ESC_PLAYER_SEE_MENU[playerid]=false;
	return true;
}

OnEscapeMenuExit()
{
	TextDrawDestroy(TD_ESC_Menu_Opt_1);
	TextDrawDestroy(TD_ESC_Menu_Opt_2);
	TextDrawDestroy(TD_ESC_Menu_Opt_3);
	TextDrawDestroy(TD_ESC_Menu_Opt_4);
	TextDrawDestroy(TD_ESC_Menu_Opt_5);
	TextDrawDestroy(TD_ESC_Menu_Opt_6);
	TextDrawDestroy(TD_ESC_Menu_Opt_7);
	TextDrawDestroy(TD_ESC_Menu_Title);
	TextDrawDestroy(TD_ESC_Menu_Backg);
	return true;
}

OnEscapeMenuConnect(playerid)return _ESC_PLAYER_SEE_MENU[playerid]=false;

OnEscapeMenuDisconnect(playerid)return HidePlayerEscapeMenu(playerid);

OnEscapeMenuUpdate(playerid)
{
	if(_ESC_PLAYER_SEE_MENU[playerid]==true&&_ESC_PLAYER_MOVE[playerid]==true)
	{
	    new Keys,ud,UNUSED_KEY;
	    GetPlayerKeys(playerid,Keys,ud,UNUSED_KEY);
	    if(ud<0)//Up
	    {
            PlayerPlaySound(playerid,ESC_SWITCH_SOUND,0,0,0);
	        _ESC_PLAYER_MOVE[playerid]=false;
	        SetTimerEx("_ESC_PLAYER_MOVE_TIMER",ESC_MOVE_TIME_DISTANCE,false,"d",playerid);
	        _ESC_PLAYER_ROW_POSITION[playerid]--;
	        if(_ESC_PLAYER_ROW_POSITION[playerid]<0)_ESC_PLAYER_ROW_POSITION[playerid]=6;
	        if(_ESC_PLAYER_FUNC_AVAILABLE[playerid][_ESC_PLAYER_ROW_POSITION[playerid]]==false){
				_ESC_PLAYER_ROW_POSITION[playerid]=6;
		        if(_ESC_PLAYER_FUNC_AVAILABLE[playerid][_ESC_PLAYER_ROW_POSITION[playerid]]==false){
					_ESC_PLAYER_ROW_POSITION[playerid]=5;
			        if(_ESC_PLAYER_FUNC_AVAILABLE[playerid][_ESC_PLAYER_ROW_POSITION[playerid]]==false){
						_ESC_PLAYER_ROW_POSITION[playerid]=4;
				        if(_ESC_PLAYER_FUNC_AVAILABLE[playerid][_ESC_PLAYER_ROW_POSITION[playerid]]==false){
							_ESC_PLAYER_ROW_POSITION[playerid]=3;
					        if(_ESC_PLAYER_FUNC_AVAILABLE[playerid][_ESC_PLAYER_ROW_POSITION[playerid]]==false){
								_ESC_PLAYER_ROW_POSITION[playerid]=2;
			}}}}}
	        CallRemoteFunction("OnPlayerEscapeMenuRowChange","dd",playerid,_ESC_PLAYER_ROW_POSITION[playerid]);
			TextDrawColor(TD_ESC_Menu_Opt_1,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_2,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_3,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_4,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_5,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_6,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_7,1786416127);
			if(_ESC_PLAYER_ROW_POSITION[playerid]==0)TextDrawColor(TD_ESC_Menu_Opt_1,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==1)TextDrawColor(TD_ESC_Menu_Opt_2,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==2)TextDrawColor(TD_ESC_Menu_Opt_3,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==3)TextDrawColor(TD_ESC_Menu_Opt_4,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==4)TextDrawColor(TD_ESC_Menu_Opt_5,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==5)TextDrawColor(TD_ESC_Menu_Opt_6,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==6)TextDrawColor(TD_ESC_Menu_Opt_7,-823266817);
	    }
	    else if(ud>0)//Down
	    {
            PlayerPlaySound(playerid,ESC_SWITCH_SOUND,0,0,0);
	        _ESC_PLAYER_MOVE[playerid]=false;
	        SetTimerEx("_ESC_PLAYER_MOVE_TIMER",ESC_MOVE_TIME_DISTANCE,false,"d",playerid);
	        _ESC_PLAYER_ROW_POSITION[playerid]++;
	        if(_ESC_PLAYER_ROW_POSITION[playerid]>6)_ESC_PLAYER_ROW_POSITION[playerid]=0;
	        if(_ESC_PLAYER_FUNC_AVAILABLE[playerid][_ESC_PLAYER_ROW_POSITION[playerid]]==false)_ESC_PLAYER_ROW_POSITION[playerid]=0;
	        CallRemoteFunction("OnPlayerEscapeMenuRowChange","dd",playerid,_ESC_PLAYER_ROW_POSITION[playerid]);
			TextDrawColor(TD_ESC_Menu_Opt_1,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_2,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_3,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_4,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_5,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_6,1786416127);
			TextDrawColor(TD_ESC_Menu_Opt_7,1786416127);
			if(_ESC_PLAYER_ROW_POSITION[playerid]==0)TextDrawColor(TD_ESC_Menu_Opt_1,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==1)TextDrawColor(TD_ESC_Menu_Opt_2,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==2)TextDrawColor(TD_ESC_Menu_Opt_3,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==3)TextDrawColor(TD_ESC_Menu_Opt_4,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==4)TextDrawColor(TD_ESC_Menu_Opt_5,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==5)TextDrawColor(TD_ESC_Menu_Opt_6,-823266817);
			else if(_ESC_PLAYER_ROW_POSITION[playerid]==6)TextDrawColor(TD_ESC_Menu_Opt_7,-823266817);
	    }
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_1);
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_2);
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_3);
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_4);
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_5);
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_6);
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_7);
    }
    return true;
}

OnEscapeMenuKeyStateChange(playerid,newkeys)
{
	if(newkeys&KEY_SECONDARY_ATTACK&&_ESC_PLAYER_SEE_MENU[playerid]==true)
	    _ESC_OnResponse(playerid,(_ESC_PLAYER_ROW_POSITION[playerid]+1));
	return true;
}

//__________________________________________________________________New Public's
forward _ESC_PLAYER_MOVE_TIMER(playerid);
public _ESC_PLAYER_MOVE_TIMER(playerid)return _ESC_PLAYER_MOVE[playerid]=true;

//_______________________________________________________________________stock's
stock _ESC_OnResponse(playerid,id)return CallRemoteFunction("OnPlayerEscapeMenuResponse","dd",playerid,id);

stock ShowPlayerEscapeMenu(playerid,Title[],Option1[],Option2[],Option3[],Option4[],Option5[],Option6[],Option7[])
{
    _ESC_PLAYER_SEE_MENU[playerid]=true;
	forEx(7,FunctionID)
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][FunctionID]=true;
	forEx(20,ChatLines)
	    SendClientMessage(playerid,-1,"");

	if(strlen(Title)==0)TextDrawSetString(TD_ESC_Menu_Title,"_");
	else TextDrawSetString(TD_ESC_Menu_Title,Title);
	if(strlen(Option1)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_1,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][0]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_1,Option1);
	if(strlen(Option2)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_2,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][1]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_2,Option2);
	if(strlen(Option3)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_3,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][2]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_3,Option3);
	if(strlen(Option4)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_4,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][3]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_4,Option4);
	if(strlen(Option5)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_5,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][4]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_5,Option5);
	if(strlen(Option6)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_6,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][5]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_6,Option6);
	if(strlen(Option7)==0)
	{
		TextDrawSetString(TD_ESC_Menu_Opt_7,"_");
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][6]=false;
	}
	else TextDrawSetString(TD_ESC_Menu_Opt_7,Option7);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Backg);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_1);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_2);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_3);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_4);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_5);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_6);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_7);
	TextDrawShowForPlayer(playerid,TD_ESC_Menu_Title);
}

stock HidePlayerEscapeMenu(playerid)
{
	if(_ESC_PLAYER_SEE_MENU[playerid]==false)return true;
	_ESC_PLAYER_SEE_MENU[playerid]=false;
	_ESC_PLAYER_ROW_POSITION[playerid]=0;
	TextDrawColor(TD_ESC_Menu_Opt_1,-823266817);
	TextDrawColor(TD_ESC_Menu_Opt_2,1786416127);
	TextDrawColor(TD_ESC_Menu_Opt_3,1786416127);
	TextDrawColor(TD_ESC_Menu_Opt_4,1786416127);
	TextDrawColor(TD_ESC_Menu_Opt_5,1786416127);
	TextDrawColor(TD_ESC_Menu_Opt_6,1786416127);
	TextDrawColor(TD_ESC_Menu_Opt_7,1786416127);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Backg);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_1);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_2);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_3);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_4);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_5);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_6);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Opt_7);
	TextDrawHideForPlayer(playerid,TD_ESC_Menu_Title);
	return true;
}

stock EscapeMenuOpen(playerid)return _ESC_PLAYER_SEE_MENU[playerid];

stock SetPlayerEscapeMenuOptionText(playerid,OptionID,NewText[])
{
	if(_ESC_PLAYER_SEE_MENU[playerid]==false)return true;
	if(OptionID<=1){
		TextDrawSetString(TD_ESC_Menu_Opt_1,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][0]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_1);
	}else if(OptionID==2){
		TextDrawSetString(TD_ESC_Menu_Opt_2,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][1]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_2);
	}else if(OptionID==3){
		TextDrawSetString(TD_ESC_Menu_Opt_3,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][2]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_3);
	}else if(OptionID==4){
		TextDrawSetString(TD_ESC_Menu_Opt_4,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][3]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_4);
	}else if(OptionID==5){
		TextDrawSetString(TD_ESC_Menu_Opt_5,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][4]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_5);
	}else if(OptionID==6){
		TextDrawSetString(TD_ESC_Menu_Opt_6,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][5]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_6);
	}else{
		TextDrawSetString(TD_ESC_Menu_Opt_7,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][6]=true;
		TextDrawShowForPlayer(playerid,TD_ESC_Menu_Opt_7);
	}
	return true;
}

stock RemovePlayerEscapeMenuOption(playerid,OptionID)
{
	if(_ESC_PLAYER_SEE_MENU[playerid]==false)return true;
	if(OptionID<=1){
		TextDrawSetString(TD_ESC_Menu_Opt_1,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][0]=false;
	}else if(OptionID==2){
		TextDrawSetString(TD_ESC_Menu_Opt_2,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][1]=false;
	}else if(OptionID==3){
		TextDrawSetString(TD_ESC_Menu_Opt_3,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][2]=false;
	}else if(OptionID==4){
		TextDrawSetString(TD_ESC_Menu_Opt_4,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][3]=false;
	}else if(OptionID==5){
		TextDrawSetString(TD_ESC_Menu_Opt_5,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][4]=false;
	}else if(OptionID==6){
		TextDrawSetString(TD_ESC_Menu_Opt_6,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][5]=false;
	}else{
		 TextDrawSetString(TD_ESC_Menu_Opt_7,NewText);
		_ESC_PLAYER_FUNC_AVAILABLE[playerid][6]=false;
	}
	return true;
}

stock IsValidEscapeMenuOption(playerid,OptionID)return _ESC_PLAYER_FUNC_AVAILABLE[playerid][OptionID];
