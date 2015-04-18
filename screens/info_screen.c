/**
 ******************************************************************************
 * @file    info_screen.c
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


D4D_CHAR str_name[31] = "";
D4D_CHAR str_mode[10] = "";
D4D_CHAR str_id[31] = "";
D4D_CHAR str_config[5] = "";
D4D_CHAR str_TempType[2] = "";
D4D_CHAR str_Firmware[5] = "";
D4D_CHAR str_IpAddress[16] = "";
D4D_CHAR str_OinkWeb[21] = "";


D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblName,     "Name:",       5, 45,  95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblMode,     "Mode:",       5, 65,  95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblId,       "Id:",         5, 85,  95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblTemp,     "Temp. Type:", 5, 130, 95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblFirmware, "Firmware:",   5, 165, 95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblIp,       "IP Address:", 5, 190, 95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblWeb,      "Oink Web:",   5, 215, 95, 20, FONT_ARIAL_11, D4D_COLOR_BLACK, OINK_COLOR_GREY);


D4D_DECLARE_STD_LABEL(scrInfo_valName,     str_name,      110, 45,  200, 20, FONT_ARIAL_11);
D4D_DECLARE_STD_LABEL(scrInfo_valMode,     str_mode,      110, 65,  200, 20, FONT_ARIAL_11);
D4D_DECLARE_STD_LABEL(scrInfo_valId,       str_id,        110, 85,  200, 20, FONT_ARIAL_11);
D4D_DECLARE_STD_LABEL(scrInfo_valTemp,     str_TempType,  110, 130, 200, 20, FONT_ARIAL_11);
D4D_DECLARE_STD_LABEL(scrInfo_valFirmware, str_Firmware,  110, 165, 200, 20, FONT_ARIAL_11);
D4D_DECLARE_STD_LABEL(scrInfo_valIp,       str_IpAddress, 110, 190, 200, 20, FONT_ARIAL_11);
D4D_DECLARE_STD_LABEL(scrInfo_valWeb,      str_OinkWeb,   110, 215, 200, 20, FONT_ARIAL_11);



D4D_DECLARE_STD_SCREEN_BEGIN(screen_info, ScreenInfo_)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnInfo)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnBrew)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm1)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm2)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblName)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblMode)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblId)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblTemp)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblFirmware)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblIp)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblWeb)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valName)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valMode)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valId)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valTemp)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valFirmware)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valIp)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_valWeb)
D4D_DECLARE_SCREEN_END()    

static void ScreenInfo_OnInit()
{
}

static void ScreenInfo_OnMain()
{
}

static void ScreenInfo_OnActivate()
{
    changeMenuButtonState((D4D_OBJECT*)&scr_btnInfo, D4D_TRUE, "Info");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnBrew, D4D_FALSE, "Brew");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnFerm1, D4D_FALSE, "Ferm 1");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnFerm2, D4D_FALSE, "Ferm 2");
}

static void ScreenInfo_OnDeactivate()
{
}

static Byte ScreenInfo_OnObjectMsg(D4D_MESSAGE* pMsg)
{
    D4D_UNUSED(pMsg);
    return 0;
}
