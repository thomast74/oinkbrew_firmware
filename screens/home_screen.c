/**
 ******************************************************************************
 * @file    home_screen.c
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
        
        
D4D_DECLARE_STD_PICTURE(scrHome_bmpLogo, 66, 10, 188, 35, &bmp_oink_logo);


D4D_DECLARE_STD_SCREEN_BEGIN(screen_home, ScreenHome_)
    D4D_DECLARE_SCREEN_OBJECT(scrHome_bmpLogo)
D4D_DECLARE_SCREEN_END()    

static void ScreenHome_OnInit()
{
}

static void ScreenHome_OnMain()
{
    
}

static void ScreenHome_OnActivate()
{
}

static void ScreenHome_OnDeactivate()
{
}

static Byte ScreenHome_OnObjectMsg(D4D_MESSAGE* pMsg)
{
    D4D_UNUSED(pMsg);
    return 0;
}
