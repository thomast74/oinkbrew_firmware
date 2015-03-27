/**
 ******************************************************************************
 * @file    startup_screen.c
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

D4D_CHAR str_message[50] = "Starting up...";
D4D_CHAR str_version[15] = "";
        
        
D4D_DECLARE_STD_PICTURE(scrStartup_bmpLogo, 60, 10, 200, 114, &bmp_oink_logo);

D4D_DECLARE_STD_LABEL_CENTER(scrStartup_message, str_message, 40, 160, 240, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL(scrStartup_version, str_version, 5, 220, 80, 20, FONT_ARIAL_10);
D4D_DECLARE_STD_LABEL(scrStartup_copyright, "(c) 2015 by Oink Brew", 185, 220, 130, 20, FONT_ARIAL_10);


D4D_DECLARE_STD_SCREEN_BEGIN(screen_startup, ScreenStartup_)
    D4D_DECLARE_SCREEN_OBJECT(scrStartup_bmpLogo)
    D4D_DECLARE_SCREEN_OBJECT(scrStartup_message)
    D4D_DECLARE_SCREEN_OBJECT(scrStartup_version)
    D4D_DECLARE_SCREEN_OBJECT(scrStartup_copyright)
D4D_DECLARE_SCREEN_END()    

static void ScreenStartup_OnInit()
{
}

static void ScreenStartup_OnMain()
{
    
}

void ScreenStartup_UpdateMessage(const char* message)
{
    D4D_SetText(&scrStartup_message, (char*)message);
    D4D_InvalidateObject(&scrStartup_message, D4D_TRUE); 
    D4D_Poll();
}

void ScreenStartup_UpdateVersion(const char* version)
{
    D4D_SetText(&scrStartup_version, (char*)version);
    D4D_InvalidateObject(&scrStartup_version, D4D_TRUE); 
    D4D_Poll();    
}

static void ScreenStartup_OnActivate()
{
}

static void ScreenStartup_OnDeactivate()
{
}

static Byte ScreenStartup_OnObjectMsg(D4D_MESSAGE* pMsg)
{
    D4D_UNUSED(pMsg);
    return 0;
}
