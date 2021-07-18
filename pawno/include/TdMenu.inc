
#include <a_samp>


/*Natives
native CreateTdMenu(menuid,menutitle[],Rows);
native AddTdMenuItem(menuid,row,menutext[],menuprices);
native ShowTdMenuForPlayer(playerid,menuid);
native HideTdMenuForPlayer(playerid,menuid);
native ShowTdMenuForAll(menuid);
native HideTdMenuForAll(menuid);
native DestroyTdMenu(menuid);
native GetPlayerTdMenu(playerid);
*/

#define MAX_TD_MENUS  100
#define MAX_TITLE_LEN 20

enum MInfo
{
bool:UsedMenu,
mRows,
}
new TdMenuTimerActive;
new Text:MenuTd00[MAX_TD_MENUS][1];
new Text:MenuTd0[MAX_TD_MENUS][1];
new Text:MenuTd1[MAX_TD_MENUS][1];
new Text:MenuTd2[MAX_TD_MENUS][1];
new Text:MenuTd3[MAX_TD_MENUS][16];
new Text:MenuTd4[MAX_TD_MENUS][16];

new CurrentPlayerMenu[MAX_PLAYERS];
new MenuInfo[MAX_TD_MENUS][MInfo];
new MenuShown[MAX_PLAYERS][MAX_TD_MENUS];

forward OnPlayerTdMenuUsed(playerid,menuid,row);

stock CreateTdMenu(menuid,menutitle[],Rows)
{
if(strlen(menutitle) > MAX_TITLE_LEN) return print("[ERROR]:Title Len Must be 20");
if(Rows > 15) return print("[ERROR]:Max Rows 15"); DestroyTdMenu(menuid);
switch(Rows)
{
case 1:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 7.500022);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);
}

case 2:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 8.600017);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);
}

case 3:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 9.700017);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);
}

case 4:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 10.800018);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);
}

case 5:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 11.900018);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);
}

case 6:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 13.000019);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);
}

case 7:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 14.100019);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);
}

case 8:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 15.200019);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);
}

case 9:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 16.300020);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);
}

case 10:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 17.400020);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);

MenuTd3[menuid][10] = TextDrawCreate(7.400001, 240.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(205.650772, 240.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);
}
case 11:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 18.600021);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);

MenuTd3[menuid][10] = TextDrawCreate(7.400001, 240.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(205.650772, 240.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);

MenuTd3[menuid][11] = TextDrawCreate(7.400001, 250.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][11], 255);
TextDrawFont(MenuTd3[menuid][11], 1);
TextDrawLetterSize(MenuTd3[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][11], -1);
TextDrawSetOutline(MenuTd3[menuid][11], 1);
TextDrawSetProportional(MenuTd3[menuid][11], 1);
TextDrawSetSelectable(MenuTd3[menuid][11], 0);

MenuTd4[menuid][11] = TextDrawCreate(205.650772, 250.000000, "");
TextDrawAlignment(MenuTd4[menuid][11], 3);
TextDrawBackgroundColor(MenuTd4[menuid][11], 255);
TextDrawFont(MenuTd4[menuid][11], 1);
TextDrawLetterSize(MenuTd4[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][11], -1);
TextDrawSetOutline(MenuTd4[menuid][11], 1);
TextDrawSetProportional(MenuTd4[menuid][11], 1);
TextDrawSetSelectable(MenuTd4[menuid][11], 0);
}
case 12:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 19.700021);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);

MenuTd3[menuid][10] = TextDrawCreate(7.400001, 240.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(205.650772, 240.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);

MenuTd3[menuid][11] = TextDrawCreate(7.400001, 250.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][11], 255);
TextDrawFont(MenuTd3[menuid][11], 1);
TextDrawLetterSize(MenuTd3[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][11], -1);
TextDrawSetOutline(MenuTd3[menuid][11], 1);
TextDrawSetProportional(MenuTd3[menuid][11], 1);
TextDrawSetSelectable(MenuTd3[menuid][11], 0);

MenuTd4[menuid][11] = TextDrawCreate(205.650772, 250.000000, "");
TextDrawAlignment(MenuTd4[menuid][11], 3);
TextDrawBackgroundColor(MenuTd4[menuid][11], 255);
TextDrawFont(MenuTd4[menuid][11], 1);
TextDrawLetterSize(MenuTd4[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][11], -1);
TextDrawSetOutline(MenuTd4[menuid][11], 1);
TextDrawSetProportional(MenuTd4[menuid][11], 1);
TextDrawSetSelectable(MenuTd4[menuid][11], 0);

MenuTd3[menuid][12] = TextDrawCreate(7.400001, 260.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][12], 255);
TextDrawFont(MenuTd3[menuid][12], 1);
TextDrawLetterSize(MenuTd3[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][12], -1);
TextDrawSetOutline(MenuTd3[menuid][12], 1);
TextDrawSetProportional(MenuTd3[menuid][12], 1);
TextDrawSetSelectable(MenuTd3[menuid][12], 0);

MenuTd4[menuid][12] = TextDrawCreate(205.650772, 260.000000, "");
TextDrawAlignment(MenuTd4[menuid][12], 3);
TextDrawBackgroundColor(MenuTd4[menuid][12], 255);
TextDrawFont(MenuTd4[menuid][12], 1);
TextDrawLetterSize(MenuTd4[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][12], -1);
TextDrawSetOutline(MenuTd4[menuid][12], 1);
TextDrawSetProportional(MenuTd4[menuid][12], 1);
TextDrawSetSelectable(MenuTd4[menuid][12], 0);

}
case 13:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 20.800022);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);

MenuTd3[menuid][10] = TextDrawCreate(7.400001, 240.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(205.650772, 240.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);

MenuTd3[menuid][11] = TextDrawCreate(7.400001, 250.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][11], 255);
TextDrawFont(MenuTd3[menuid][11], 1);
TextDrawLetterSize(MenuTd3[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][11], -1);
TextDrawSetOutline(MenuTd3[menuid][11], 1);
TextDrawSetProportional(MenuTd3[menuid][11], 1);
TextDrawSetSelectable(MenuTd3[menuid][11], 0);

MenuTd4[menuid][11] = TextDrawCreate(205.650772, 250.000000, "");
TextDrawAlignment(MenuTd4[menuid][11], 3);
TextDrawBackgroundColor(MenuTd4[menuid][11], 255);
TextDrawFont(MenuTd4[menuid][11], 1);
TextDrawLetterSize(MenuTd4[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][11], -1);
TextDrawSetOutline(MenuTd4[menuid][11], 1);
TextDrawSetProportional(MenuTd4[menuid][11], 1);
TextDrawSetSelectable(MenuTd4[menuid][11], 0);

MenuTd3[menuid][12] = TextDrawCreate(7.400001, 260.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][12], 255);
TextDrawFont(MenuTd3[menuid][12], 1);
TextDrawLetterSize(MenuTd3[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][12], -1);
TextDrawSetOutline(MenuTd3[menuid][12], 1);
TextDrawSetProportional(MenuTd3[menuid][12], 1);
TextDrawSetSelectable(MenuTd3[menuid][12], 0);

MenuTd4[menuid][12] = TextDrawCreate(205.650772, 260.000000, "");
TextDrawAlignment(MenuTd4[menuid][12], 3);
TextDrawBackgroundColor(MenuTd4[menuid][12], 255);
TextDrawFont(MenuTd4[menuid][12], 1);
TextDrawLetterSize(MenuTd4[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][12], -1);
TextDrawSetOutline(MenuTd4[menuid][12], 1);
TextDrawSetProportional(MenuTd4[menuid][12], 1);
TextDrawSetSelectable(MenuTd4[menuid][12], 0);

MenuTd3[menuid][13] = TextDrawCreate(7.400001, 270.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][13], 255);
TextDrawFont(MenuTd3[menuid][13], 1);
TextDrawLetterSize(MenuTd3[menuid][13], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][13], -1);
TextDrawSetOutline(MenuTd3[menuid][13], 1);
TextDrawSetProportional(MenuTd3[menuid][13], 1);
TextDrawSetSelectable(MenuTd3[menuid][13], 0);

MenuTd4[menuid][13] = TextDrawCreate(205.650772, 270.000000, "");
TextDrawAlignment(MenuTd4[menuid][13], 3);
TextDrawBackgroundColor(MenuTd4[menuid][13], 255);
TextDrawFont(MenuTd4[menuid][13], 1);
TextDrawLetterSize(MenuTd4[menuid][13], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][13], -1);
TextDrawSetOutline(MenuTd4[menuid][13], 1);
TextDrawSetProportional(MenuTd4[menuid][13], 1);
TextDrawSetSelectable(MenuTd4[menuid][13], 0);
}
case 14:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 21.900022);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);

MenuTd3[menuid][10] = TextDrawCreate(7.400001, 240.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(205.650772, 240.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);

MenuTd3[menuid][11] = TextDrawCreate(7.400001, 250.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][11], 255);
TextDrawFont(MenuTd3[menuid][11], 1);
TextDrawLetterSize(MenuTd3[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][11], -1);
TextDrawSetOutline(MenuTd3[menuid][11], 1);
TextDrawSetProportional(MenuTd3[menuid][11], 1);
TextDrawSetSelectable(MenuTd3[menuid][11], 0);

MenuTd4[menuid][11] = TextDrawCreate(205.650772, 250.000000, "");
TextDrawAlignment(MenuTd4[menuid][11], 3);
TextDrawBackgroundColor(MenuTd4[menuid][11], 255);
TextDrawFont(MenuTd4[menuid][11], 1);
TextDrawLetterSize(MenuTd4[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][11], -1);
TextDrawSetOutline(MenuTd4[menuid][11], 1);
TextDrawSetProportional(MenuTd4[menuid][11], 1);
TextDrawSetSelectable(MenuTd4[menuid][11], 0);

MenuTd3[menuid][12] = TextDrawCreate(7.400001, 260.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][12], 255);
TextDrawFont(MenuTd3[menuid][12], 1);
TextDrawLetterSize(MenuTd3[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][12], -1);
TextDrawSetOutline(MenuTd3[menuid][12], 1);
TextDrawSetProportional(MenuTd3[menuid][12], 1);
TextDrawSetSelectable(MenuTd3[menuid][12], 0);

MenuTd4[menuid][12] = TextDrawCreate(205.650772, 260.000000, "");
TextDrawAlignment(MenuTd4[menuid][12], 3);
TextDrawBackgroundColor(MenuTd4[menuid][12], 255);
TextDrawFont(MenuTd4[menuid][12], 1);
TextDrawLetterSize(MenuTd4[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][12], -1);
TextDrawSetOutline(MenuTd4[menuid][12], 1);
TextDrawSetProportional(MenuTd4[menuid][12], 1);
TextDrawSetSelectable(MenuTd4[menuid][12], 0);

MenuTd3[menuid][13] = TextDrawCreate(7.400001, 270.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][13], 255);
TextDrawFont(MenuTd3[menuid][13], 1);
TextDrawLetterSize(MenuTd3[menuid][13], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][13], -1);
TextDrawSetOutline(MenuTd3[menuid][13], 1);
TextDrawSetProportional(MenuTd3[menuid][13], 1);
TextDrawSetSelectable(MenuTd3[menuid][13], 0);

MenuTd4[menuid][13] = TextDrawCreate(205.650772, 270.000000, "");
TextDrawAlignment(MenuTd4[menuid][13], 3);
TextDrawBackgroundColor(MenuTd4[menuid][13], 255);
TextDrawFont(MenuTd4[menuid][13], 1);
TextDrawLetterSize(MenuTd4[menuid][13], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][13], -1);
TextDrawSetOutline(MenuTd4[menuid][13], 1);
TextDrawSetProportional(MenuTd4[menuid][13], 1);
TextDrawSetSelectable(MenuTd4[menuid][13], 0);

MenuTd3[menuid][14] = TextDrawCreate(7.400001, 280.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][14], 255);
TextDrawFont(MenuTd3[menuid][14], 1);
TextDrawLetterSize(MenuTd3[menuid][14], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][14], -1);
TextDrawSetOutline(MenuTd3[menuid][14], 1);
TextDrawSetProportional(MenuTd3[menuid][14], 1);
TextDrawSetSelectable(MenuTd3[menuid][14], 0);

MenuTd4[menuid][14] = TextDrawCreate(205.650772, 280.000000, "");
TextDrawAlignment(MenuTd4[menuid][14], 3);
TextDrawBackgroundColor(MenuTd4[menuid][14], 255);
TextDrawFont(MenuTd4[menuid][14], 1);
TextDrawLetterSize(MenuTd4[menuid][14], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][14], -1);
TextDrawSetOutline(MenuTd4[menuid][14], 1);
TextDrawSetProportional(MenuTd4[menuid][14], 1);
TextDrawSetSelectable(MenuTd4[menuid][14], 0);
}
case 15:
{
MenuTd00[menuid][0] = TextDrawCreate(2.050008, 119.349983, "LD_SPAC:white");
TextDrawLetterSize(MenuTd00[menuid][0], 0.000000, 0.000000);
TextDrawTextSize(MenuTd00[menuid][0], 213.150100, 14.306253);
TextDrawAlignment(MenuTd00[menuid][0], 1);
TextDrawColor(MenuTd00[menuid][0], 65535);
TextDrawSetShadow(MenuTd00[menuid][0], 0);
TextDrawSetOutline(MenuTd00[menuid][0], 0);
TextDrawFont(MenuTd00[menuid][0], 4);

MenuTd0[menuid][0] = TextDrawCreate(217.199768, 135.375076, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 23.000022);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 0.449998, 0.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(110.150039, 121.362541, menutitle);
TextDrawLetterSize(MenuTd1[menuid][0], 0.211999, 1.018126);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawColor(MenuTd1[menuid][0], 8388863);
TextDrawSetShadow(MenuTd1[menuid][0], 0);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 2);
TextDrawSetProportional(MenuTd1[menuid][0], 1);

MenuTd2[menuid][0] = TextDrawCreate(109.250030, 137.374969, "Press ~y~F6 [T] ~w~And Select Number~n~~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawLetterSize(MenuTd2[menuid][0], 0.172049, 0.691312);
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetShadow(MenuTd2[menuid][0], 0);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);

MenuTd3[menuid][1] = TextDrawCreate(7.400001, 169.956115, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(205.650772, 150.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);

MenuTd3[menuid][2] = TextDrawCreate(7.400001, 160.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(205.650772, 160.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);

MenuTd3[menuid][3] = TextDrawCreate(7.400001, 170.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(205.650772, 170.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);

MenuTd3[menuid][4] = TextDrawCreate(7.400001, 180.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(205.650772, 180.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);

MenuTd3[menuid][5] = TextDrawCreate(7.400001, 190.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(205.650772, 190.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);

MenuTd3[menuid][6] = TextDrawCreate(7.400001, 200.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(205.650772, 200.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);

MenuTd3[menuid][7] = TextDrawCreate(7.400001, 210.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(205.650772, 210.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);

MenuTd3[menuid][8] = TextDrawCreate(7.400001, 220.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(205.650772, 220.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);

MenuTd3[menuid][9] = TextDrawCreate(7.400001, 230.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(205.650772, 230.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);

MenuTd3[menuid][10] = TextDrawCreate(7.400001, 240.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(205.650772, 240.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);

MenuTd3[menuid][11] = TextDrawCreate(7.400001, 250.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][11], 255);
TextDrawFont(MenuTd3[menuid][11], 1);
TextDrawLetterSize(MenuTd3[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][11], -1);
TextDrawSetOutline(MenuTd3[menuid][11], 1);
TextDrawSetProportional(MenuTd3[menuid][11], 1);
TextDrawSetSelectable(MenuTd3[menuid][11], 0);

MenuTd4[menuid][11] = TextDrawCreate(205.650772, 250.000000, "");
TextDrawAlignment(MenuTd4[menuid][11], 3);
TextDrawBackgroundColor(MenuTd4[menuid][11], 255);
TextDrawFont(MenuTd4[menuid][11], 1);
TextDrawLetterSize(MenuTd4[menuid][11], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][11], -1);
TextDrawSetOutline(MenuTd4[menuid][11], 1);
TextDrawSetProportional(MenuTd4[menuid][11], 1);
TextDrawSetSelectable(MenuTd4[menuid][11], 0);

MenuTd3[menuid][12] = TextDrawCreate(7.400001, 260.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][12], 255);
TextDrawFont(MenuTd3[menuid][12], 1);
TextDrawLetterSize(MenuTd3[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][12], -1);
TextDrawSetOutline(MenuTd3[menuid][12], 1);
TextDrawSetProportional(MenuTd3[menuid][12], 1);
TextDrawSetSelectable(MenuTd3[menuid][12], 0);

MenuTd4[menuid][12] = TextDrawCreate(205.650772, 260.000000, "");
TextDrawAlignment(MenuTd4[menuid][12], 3);
TextDrawBackgroundColor(MenuTd4[menuid][12], 255);
TextDrawFont(MenuTd4[menuid][12], 1);
TextDrawLetterSize(MenuTd4[menuid][12], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][12], -1);
TextDrawSetOutline(MenuTd4[menuid][12], 1);
TextDrawSetProportional(MenuTd4[menuid][12], 1);
TextDrawSetSelectable(MenuTd4[menuid][12], 0);

MenuTd3[menuid][13] = TextDrawCreate(7.400001, 270.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][13], 255);
TextDrawFont(MenuTd3[menuid][13], 1);
TextDrawLetterSize(MenuTd3[menuid][13], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][13], -1);
TextDrawSetOutline(MenuTd3[menuid][13], 1);
TextDrawSetProportional(MenuTd3[menuid][13], 1);
TextDrawSetSelectable(MenuTd3[menuid][13], 0);

MenuTd4[menuid][13] = TextDrawCreate(205.650772, 270.000000, "");
TextDrawAlignment(MenuTd4[menuid][13], 3);
TextDrawBackgroundColor(MenuTd4[menuid][13], 255);
TextDrawFont(MenuTd4[menuid][13], 1);
TextDrawLetterSize(MenuTd4[menuid][13], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][13], -1);
TextDrawSetOutline(MenuTd4[menuid][13], 1);
TextDrawSetProportional(MenuTd4[menuid][13], 1);
TextDrawSetSelectable(MenuTd4[menuid][13], 0);

MenuTd3[menuid][14] = TextDrawCreate(7.400001, 280.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][14], 255);
TextDrawFont(MenuTd3[menuid][14], 1);
TextDrawLetterSize(MenuTd3[menuid][14], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][14], -1);
TextDrawSetOutline(MenuTd3[menuid][14], 1);
TextDrawSetProportional(MenuTd3[menuid][14], 1);
TextDrawSetSelectable(MenuTd3[menuid][14], 0);

MenuTd4[menuid][14] = TextDrawCreate(205.650772, 280.000000, "");
TextDrawAlignment(MenuTd4[menuid][14], 3);
TextDrawBackgroundColor(MenuTd4[menuid][14], 255);
TextDrawFont(MenuTd4[menuid][14], 1);
TextDrawLetterSize(MenuTd4[menuid][14], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][14], -1);
TextDrawSetOutline(MenuTd4[menuid][14], 1);
TextDrawSetProportional(MenuTd4[menuid][14], 1);
TextDrawSetSelectable(MenuTd4[menuid][14], 0);

MenuTd3[menuid][15] = TextDrawCreate(7.400001, 290.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][15], 255);
TextDrawFont(MenuTd3[menuid][15], 1);
TextDrawLetterSize(MenuTd3[menuid][15], 0.215645, 0.758686);
TextDrawColor(MenuTd3[menuid][15], -1);
TextDrawSetOutline(MenuTd3[menuid][15], 1);
TextDrawSetProportional(MenuTd3[menuid][15], 1);
TextDrawSetSelectable(MenuTd3[menuid][15], 0);

MenuTd4[menuid][15] = TextDrawCreate(205.650772, 290.000000, "");
TextDrawAlignment(MenuTd4[menuid][15], 3);
TextDrawBackgroundColor(MenuTd4[menuid][15], 255);
TextDrawFont(MenuTd4[menuid][15], 1);
TextDrawLetterSize(MenuTd4[menuid][15], 0.215645, 0.758686);
TextDrawColor(MenuTd4[menuid][15], -1);
TextDrawSetOutline(MenuTd4[menuid][15], 1);
TextDrawSetProportional(MenuTd4[menuid][15], 1);
TextDrawSetSelectable(MenuTd4[menuid][15], 0);
}
}
MenuInfo[menuid][mRows] = Rows;
MenuInfo[menuid][UsedMenu] = true;
if(TdMenuTimerActive != 1)
{
SetTimer("TdMenuTimer",50,1);
TdMenuTimerActive = 1;
}
return 1;
}


stock AddTdMenuItem(menuid,row,menutext[],Itemprices = 0)
{
if(MenuInfo[menuid][UsedMenu] == true)
{
if(Itemprices > 0)
{
if(row > MenuInfo[menuid][mRows]) return 1;
if(row == 1)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~g~1. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][1],Str1);
TextDrawSetString(MenuTd4[menuid][1],Str);
}
if(row == 2)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~2. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][2],Str1);
TextDrawSetString(MenuTd4[menuid][2],Str);
}
if(row == 3)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~3. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][3],Str1);
TextDrawSetString(MenuTd4[menuid][3],Str);
}
if(row == 4)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~4. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][4],Str1);
TextDrawSetString(MenuTd4[menuid][4],Str);
}
if(row == 5)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~5. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][5],Str1);
TextDrawSetString(MenuTd4[menuid][5],Str);
}
if(row == 6)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~6. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][6],Str1);
TextDrawSetString(MenuTd4[menuid][6],Str);
}
if(row == 7)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~7. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][7],Str1);
TextDrawSetString(MenuTd4[menuid][7],Str);
}
if(row == 8)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~8. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][8],Str1);
TextDrawSetString(MenuTd4[menuid][8],Str);
}
if(row == 9)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~9. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][9],Str1);
TextDrawSetString(MenuTd4[menuid][9],Str);
}
if(row == 10)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~10. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][10],Str1);
TextDrawSetString(MenuTd4[menuid][10],Str);
}
if(row == 11)
{
new Str[512];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~11. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][11],Str1);
TextDrawSetString(MenuTd4[menuid][11],Str);
}
if(row == 12)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~12. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][12],Str1);
TextDrawSetString(MenuTd4[menuid][12],Str);
}
if(row == 13)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~13. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][13],Str1);
TextDrawSetString(MenuTd4[menuid][13],Str);
}
if(row == 14)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~14. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][14],Str1);
TextDrawSetString(MenuTd4[menuid][14],Str);
}
if(row == 15)
{
new Str[256];
format(Str,sizeof(Str),"~n~~n~~n~~g~%s",formatInt(Itemprices));
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~15. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][15],Str1);
TextDrawSetString(MenuTd4[menuid][15],Str);
}
}
else
{
if(row == 1)
{
new Str1[700];
format(Str1,sizeof(Str1),"~g~1. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][1],Str1);
TextDrawSetString(MenuTd4[menuid][1],"");
}
if(row == 2)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~2. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][2],Str1);
TextDrawSetString(MenuTd4[menuid][1],"");
}
if(row == 3)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~3. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][3],Str1);
TextDrawSetString(MenuTd4[menuid][1],"");
}
if(row == 4)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~4. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][4],Str1);
TextDrawSetString(MenuTd4[menuid][1],"");
}
if(row == 5)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~5. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][5],Str1);
TextDrawSetString(MenuTd4[menuid][5],"");
}
if(row == 6)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~6. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][6],Str1);
TextDrawSetString(MenuTd4[menuid][6],"");
}
if(row == 7)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~7. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][7],Str1);
TextDrawSetString(MenuTd4[menuid][7],"");
}
if(row == 8)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~8. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][8],Str1);
TextDrawSetString(MenuTd4[menuid][8],"");
}
if(row == 9)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~9. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][9],Str1);
TextDrawSetString(MenuTd4[menuid][9],"");
}
if(row == 10)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~10. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][10],Str1);
TextDrawSetString(MenuTd4[menuid][10],"");
}
if(row == 11)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~11. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][11],Str1);
TextDrawSetString(MenuTd4[menuid][11],"");
}
if(row == 12)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~12. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][12],Str1);
TextDrawSetString(MenuTd4[menuid][12],"");
}
if(row == 13)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~13. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][13],Str1);
TextDrawSetString(MenuTd4[menuid][13],"");
}
if(row == 14)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~14. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][14],Str1);
TextDrawSetString(MenuTd4[menuid][14],"");
}
if(row == 15)
{
new Str1[700];
format(Str1,sizeof(Str1),"~n~~n~~n~~g~15. ~w~%s",menutext);
TextDrawSetString(MenuTd3[menuid][15],Str1);
TextDrawSetString(MenuTd4[menuid][15],"");
}
}
}
return 1;
}


stock ShowTdMenuForPlayer(playerid,menuid)
{
if(IsPlayerConnected(playerid))
{
for(new m;m<MAX_TD_MENUS;m++)
{
if(MenuShown[playerid][m] == 1)
{
TextDrawHideForPlayer(playerid,MenuTd00[m][0]);
TextDrawHideForPlayer(playerid,MenuTd0[m][0]);
TextDrawHideForPlayer(playerid,MenuTd1[m][0]);
TextDrawHideForPlayer(playerid,MenuTd2[m][0]);
for(new m11;m11<16;m11++)
{
TextDrawHideForPlayer(playerid,MenuTd3[m][m11]);
TextDrawHideForPlayer(playerid,MenuTd4[m][m11]);
}
MenuShown[playerid][m] = false;
}
}

switch(MenuInfo[menuid][mRows])
{
case 1:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
}
case 2:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
}
case 3:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
}
case 4:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
}
case 5:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
}
case 6:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
}
case 7:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
}
case 8:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
}
case 9:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
}
case 10:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
}
case 11:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
}
case 12:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
}
case 13:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][13]);
}
case 14:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][14]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][14]);
}
case 15:
{
TextDrawShowForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][14]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][14]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][15]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][15]);
}
}
CurrentPlayerMenu[playerid] = menuid;
MenuShown[playerid][menuid] = true;
}
}
stock ShowTdMenuForAll(menuid)
{
for(new i;i<MAX_PLAYERS;i++)
{
if(IsPlayerConnected(i))
{
for(new m;m<MAX_TD_MENUS;m++)
{
if(MenuShown[i][m] == 1)
{
TextDrawHideForAll(MenuTd00[m][0]);
TextDrawHideForAll(MenuTd0[m][0]);
TextDrawHideForAll(MenuTd1[m][0]);
TextDrawHideForAll(MenuTd2[m][0]);
for(new m11;m11<16;m11++)
{
TextDrawHideForAll(MenuTd3[m][m11]);
TextDrawHideForAll(MenuTd4[m][m11]);
}
MenuShown[i][m] = false;
}
}

switch(MenuInfo[menuid][mRows])
{
case 1:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
}
case 2:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
}
case 3:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
}
case 4:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
}
case 5:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
}
case 6:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
}
case 7:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
}
case 8:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
}
case 9:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
}
case 10:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
TextDrawShowForAll(MenuTd3[menuid][10]);
TextDrawShowForAll(MenuTd4[menuid][10]);
}
case 11:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
TextDrawShowForAll(MenuTd3[menuid][10]);
TextDrawShowForAll(MenuTd4[menuid][10]);
TextDrawShowForAll(MenuTd3[menuid][11]);
TextDrawShowForAll(MenuTd4[menuid][11]);
}
case 12:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
TextDrawShowForAll(MenuTd3[menuid][10]);
TextDrawShowForAll(MenuTd4[menuid][10]);
TextDrawShowForAll(MenuTd3[menuid][11]);
TextDrawShowForAll(MenuTd4[menuid][11]);
TextDrawShowForAll(MenuTd3[menuid][12]);
TextDrawShowForAll(MenuTd4[menuid][12]);
}
case 13:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
TextDrawShowForAll(MenuTd3[menuid][10]);
TextDrawShowForAll(MenuTd4[menuid][10]);
TextDrawShowForAll(MenuTd3[menuid][11]);
TextDrawShowForAll(MenuTd4[menuid][11]);
TextDrawShowForAll(MenuTd3[menuid][12]);
TextDrawShowForAll(MenuTd4[menuid][12]);
TextDrawShowForAll(MenuTd3[menuid][13]);
TextDrawShowForAll(MenuTd4[menuid][13]);
}
case 14:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
TextDrawShowForAll(MenuTd3[menuid][10]);
TextDrawShowForAll(MenuTd4[menuid][10]);
TextDrawShowForAll(MenuTd3[menuid][11]);
TextDrawShowForAll(MenuTd4[menuid][11]);
TextDrawShowForAll(MenuTd3[menuid][12]);
TextDrawShowForAll(MenuTd4[menuid][12]);
TextDrawShowForAll(MenuTd3[menuid][13]);
TextDrawShowForAll(MenuTd4[menuid][13]);
TextDrawShowForAll(MenuTd3[menuid][14]);
TextDrawShowForAll(MenuTd4[menuid][14]);
}
case 15:
{
TextDrawShowForAll(MenuTd00[menuid][0]);
TextDrawShowForAll(MenuTd0[menuid][0]);
TextDrawShowForAll(MenuTd1[menuid][0]);
TextDrawShowForAll(MenuTd2[menuid][0]);
TextDrawShowForAll(MenuTd3[menuid][1]);
TextDrawShowForAll(MenuTd4[menuid][1]);
TextDrawShowForAll(MenuTd3[menuid][2]);
TextDrawShowForAll(MenuTd4[menuid][2]);
TextDrawShowForAll(MenuTd3[menuid][3]);
TextDrawShowForAll(MenuTd4[menuid][3]);
TextDrawShowForAll(MenuTd3[menuid][4]);
TextDrawShowForAll(MenuTd4[menuid][4]);
TextDrawShowForAll(MenuTd3[menuid][5]);
TextDrawShowForAll(MenuTd4[menuid][5]);
TextDrawShowForAll(MenuTd3[menuid][6]);
TextDrawShowForAll(MenuTd4[menuid][6]);
TextDrawShowForAll(MenuTd3[menuid][7]);
TextDrawShowForAll(MenuTd4[menuid][7]);
TextDrawShowForAll(MenuTd3[menuid][8]);
TextDrawShowForAll(MenuTd4[menuid][8]);
TextDrawShowForAll(MenuTd3[menuid][9]);
TextDrawShowForAll(MenuTd4[menuid][9]);
TextDrawShowForAll(MenuTd3[menuid][10]);
TextDrawShowForAll(MenuTd4[menuid][10]);
TextDrawShowForAll(MenuTd3[menuid][11]);
TextDrawShowForAll(MenuTd4[menuid][11]);
TextDrawShowForAll(MenuTd3[menuid][12]);
TextDrawShowForAll(MenuTd4[menuid][12]);
TextDrawShowForAll(MenuTd3[menuid][13]);
TextDrawShowForAll(MenuTd4[menuid][13]);
TextDrawShowForAll(MenuTd3[menuid][14]);
TextDrawShowForAll(MenuTd4[menuid][14]);
TextDrawShowForAll(MenuTd3[menuid][15]);
TextDrawShowForAll(MenuTd4[menuid][15]);
}
}
CurrentPlayerMenu[i] = menuid;
MenuShown[i][menuid] = true;
}
}
}
stock HideTdMenuForPlayer(playerid,menuid)
{
if(MenuShown[playerid][menuid] == 1)
{
TextDrawHideForPlayer(playerid,MenuTd00[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd2[menuid][0]);
for(new m;m<16;m++)
{
TextDrawHideForPlayer(playerid,MenuTd3[menuid][m]);
TextDrawHideForPlayer(playerid,MenuTd4[menuid][m]);
}
CurrentPlayerMenu[playerid] = -1;
MenuShown[playerid][menuid] = false;
}
}
stock HideTdMenuForAll(menuid)
{
for(new i;i<MAX_PLAYERS;i++)
{
if(MenuShown[i][menuid] == 1)
{
TextDrawHideForAll(MenuTd00[menuid][0]);
TextDrawHideForAll(MenuTd0[menuid][0]);
TextDrawHideForAll(MenuTd1[menuid][0]);
TextDrawHideForAll(MenuTd2[menuid][0]);
for(new m;m<16;m++)
{
TextDrawHideForAll(MenuTd3[menuid][m]);
TextDrawHideForAll(MenuTd4[menuid][m]);
}
CurrentPlayerMenu[i] = -1;
MenuShown[i][menuid] = false;
}
}
}
stock DestroyTdMenu(menuid)
{
if(MenuInfo[menuid][UsedMenu] == true)
{
for(new i;i<MAX_PLAYERS;i++)
{
for(new m;m<10;m++)
{
TextDrawHideForPlayer(i,MenuTd00[menuid][m]);
TextDrawHideForPlayer(i,MenuTd0[menuid][m]);
TextDrawHideForPlayer(i,MenuTd1[menuid][m]);
TextDrawHideForPlayer(i,MenuTd2[menuid][m]);
}
for(new mi;mi<16;mi++)
{
TextDrawHideForPlayer(i,MenuTd3[menuid][mi]);
TextDrawHideForPlayer(i,MenuTd4[menuid][mi]);
}
}
}
}
#define TEXT:(%1,%2) if(MenuInfo[CurrentPlayerMenu[playerid]][mRows] == %2) if(strcmp(#%1, text, true, 10) == 0)


stock GetPlayerTdMenu(playerid)
{
if(MenuShown[playerid][CurrentPlayerMenu[playerid]] == 0) return 1;
return CurrentPlayerMenu[playerid];
}

forward	TdMenuTimer();

public TdMenuTimer()
{
	for(new i;i<MAX_PLAYERS;i++)
	{
	new keys, updown, leftright;
	GetPlayerKeys(i, keys, updown, leftright);
	if(keys == KEY_FIRE)
	{
	HideTdMenuForPlayer(i,CurrentPlayerMenu[i]);
	}
	if(!IsPlayerConnected(i))
	{
	HideTdMenuForPlayer(i,CurrentPlayerMenu[i]);
	}
	}
}

stock isNumeric(const string[])
{
  new length=strlen(string);
  if (length==0) return false;
  for (new i = 0; i < length; i++)
    {
      if (
            (string[i] > '9' || string[i] < '0' && string[i]!='-' && string[i]!='+') // Not a number,'+' or '-'
             || (string[i]=='-' && i!=0)                                             // A '-' but not at first.
             || (string[i]=='+' && i!=0)                                             // A '+' but not at first.
         ) return false;
    }
  if (length==1 && (string[0]=='-' || string[0]=='+')) return false;
  return true;
}

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}











