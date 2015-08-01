/**
 ******************************************************************************
 * @file    brew_screen.c
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-25
 * @brief   Oink Brew Spark Core Firmware
 ******************************************************************************
  Copyright (c) 2015 Oink Brew;  All rights reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */


#include "d4d.h"
#include "fonts.h"
#include "oink_logo.h"
#include "common_screen.h"
#include "widget_color_scheme.h"


#define INITIAL_BLOCK_COLOR D4D_COLOR_RGB(32,32,32)


D4D_CHAR str_brew_name[31] = "";

D4D_CHAR str_curHlt[8] = "-.-";
D4D_CHAR str_curMash[8] = "-.-";
D4D_CHAR str_curBoil[8] = "-.-";

D4D_CHAR str_tarHlt[8] = "-.-";
D4D_CHAR str_tarMash[8] = "-.-";
D4D_CHAR str_tarBoil[8] = "-.-";

D4D_CHAR str_togoHlt[9] = "";
D4D_CHAR str_togoMash[9] = "";
D4D_CHAR str_togoBoil[9] = "";

D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_lblName, "Name:", 5, 45,  95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL(scrBrew_Name, str_brew_name, 110, 45,  200, 20, FONT_ARIAL_11)


D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Hlt,      "HLT",         15,  70,  90,  25, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_curHlt,   str_curHlt,    15,  95,  90,  60, FONT_NUMBER_MEDIUM, OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_tarHlt,   str_tarHlt,    15, 155,  90,  30, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_togoHlt,  str_togoHlt,   15, 185,  90,  30, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);


D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Mash,     "Mash",       115,  70,  90,  25, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_curMash,  str_curMash,  115,  95,  90,  60, FONT_NUMBER_MEDIUM, OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_tarMash,  str_tarMash,  115, 155,  90,  30, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_togoMash, str_togoMash, 115, 185,  90,  30, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);


D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Boil,     "Boil",       215,  70,  90,  25, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_curBoil,  str_curBoil,  215,  95,  90,  60, FONT_NUMBER_MEDIUM, OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_tarBoil,  str_tarBoil,  215, 155,  90,  30, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_togoBoil, str_togoBoil, 215, 185,  90,  30, FONT_ARIAL_11,      OINK_COLOR_DARKGREY, D4D_COLOR_WHITE);

        
D4D_DECLARE_STD_SCREEN_BEGIN(screen_brew, ScreenBrew_)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnInfo)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnBrew)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm)

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_lblName)
	D4D_DECLARE_SCREEN_OBJECT(scrBrew_Name)

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_Hlt)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_Mash)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_Boil)

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curHlt)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curMash)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curBoil)

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarHlt)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarMash)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarBoil)

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_togoHlt)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_togoMash)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_togoBoil)
D4D_DECLARE_SCREEN_END()    

static void ScreenBrew_OnInit()
{
}

static void ScreenBrew_OnMain()
{
    
}

static void ScreenBrew_OnActivate()
{
    changeMenuButtonState((D4D_OBJECT*)&scr_btnInfo, D4D_FALSE, "Info");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnBrew, D4D_TRUE, "Brew");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnFerm, D4D_FALSE, "Ferm");
}

static void ScreenBrew_OnDeactivate()
{
}

static Byte ScreenBrew_OnObjectMsg(D4D_MESSAGE* pMsg)
{
    D4D_UNUSED(pMsg);
    return 0;
}
