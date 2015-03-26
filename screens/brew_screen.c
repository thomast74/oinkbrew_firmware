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
        


D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_Process,    "Process:",     5, 40,  100, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Current,   "Current",    130, 65,   70, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Target,    "Target",     220, 65,   70, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_HltIn,      "HLT In:",      5, 90,  90, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_HltOut,     "HLT Out:",     5, 110, 90, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_MashIn,     "Mash In:",     5, 135, 90, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_MashOut,    "Mash Out:",    5, 155, 90, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_BoilIn,     "Boil In:",     5, 180, 90, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_BoilInside, "Boil Inside:", 5, 200, 90, 20, FONT_ARIAL_12);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_BoilOut,    "Boil Out:",    5, 220, 90, 20, FONT_ARIAL_12);
        
        
D4D_DECLARE_STD_SCREEN_BEGIN(screen_brew, ScreenBrew_)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnInfo)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnBrew)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm1)
    D4D_DECLARE_SCREEN_OBJECT(scr_btnFerm2)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_Process)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_Current)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_Target)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_HltIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_HltOut)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_MashIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_MashOut)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_BoilIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_BoilInside)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_BoilOut)
D4D_DECLARE_SCREEN_END()    

static void ScreenBrew_OnInit()
{
}

static void ScreenBrew_OnMain()
{
    
}

static void ScreenBrew_OnActivate()
{
    changeMenuButtonState((D4D_OBJECT*)&scr_btnInfo, D4D_FALSE, "i");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnBrew, D4D_TRUE, "Brew");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnFerm1, D4D_FALSE, "Ferm 1");
    changeMenuButtonState((D4D_OBJECT*)&scr_btnFerm2, D4D_FALSE, "Ferm 2");    
}

static void ScreenBrew_OnDeactivate()
{
}

static Byte ScreenBrew_OnObjectMsg(D4D_MESSAGE* pMsg)
{
    D4D_UNUSED(pMsg);
    return 0;
}
