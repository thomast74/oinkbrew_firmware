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
        

D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblMode, "Mode:",         10, 65,  110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblId, "Id:",             10, 85,  110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblName, "Name:",         10, 45,  110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblConfig, "Config:",     10, 105, 110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblTemp, "Temp. Type:",   10, 130, 110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblFirmware, "Firmware:", 10, 165, 110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblIp, "IP Address:",     10, 190, 110, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrInfo_lblWeb, "Oink Web:",      10, 215, 110, 20, FONT_ARIAL_12);


D4D_DECLARE_STD_SCREEN_BEGIN(screen_info, ScreenInfo_)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnInfo)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnBrew)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm1)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm2)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblName)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblMode)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblId)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblConfig)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblTemp)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblFirmware)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblIp)
    D4D_DECLARE_SCREEN_OBJECT(scrInfo_lblWeb)

D4D_DECLARE_SCREEN_END()    

static void ScreenInfo_OnInit()
{
}

static void ScreenInfo_OnMain()
{
}

static void ScreenInfo_OnActivate()
{
    changeMenuButtonState((D4D_OBJECT*)&scr_btnInfo, D4D_TRUE, "i");
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
