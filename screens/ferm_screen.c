/**
 ******************************************************************************
 * @file    ferm_screen.c
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-07-18
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


D4D_CHAR str_ferm_name[31] = "";


D4D_DECLARE_STD_LABEL_RIGHT(scrFerm_lblName, "Name:", 5, 45,  95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL(scrFerm_Name, str_ferm_name, 110, 45,  200, 20, FONT_ARIAL_11)

        
D4D_DECLARE_STD_SCREEN_BEGIN(screen_ferm, ScreenFerm_)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnInfo)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnBrew)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm)

    D4D_DECLARE_SCREEN_OBJECT(scrFerm_lblName)
	D4D_DECLARE_SCREEN_OBJECT(scrFerm_Name)
D4D_DECLARE_SCREEN_END()    


static void ScreenFerm_OnInit()
{
}

static void ScreenFerm_OnMain()
{
    
}

static void ScreenFerm_OnActivate()
{
    changeMenuButtonState((D4D_OBJECT*)&scr_btnInfo, D4D_FALSE, "Info");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnBrew, D4D_FALSE, "Brew");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnFerm, D4D_TRUE, "Ferm");
}

static void ScreenFerm_OnDeactivate()
{
}

static Byte ScreenFerm_OnObjectMsg(D4D_MESSAGE* pMsg)
{
    D4D_UNUSED(pMsg);
    return 0;
}
