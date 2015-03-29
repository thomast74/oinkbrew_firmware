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


D4D_CHAR str_Process[25] = "";

D4D_CHAR str_curHltIn[8] = "";
D4D_CHAR str_curHltOut[8] = "";
D4D_CHAR str_curMashIn[8] = "";
D4D_CHAR str_curMashOut[8] = "";
D4D_CHAR str_curBoilIn[8] = "";
D4D_CHAR str_curBoilInside[8] = "";
D4D_CHAR str_curBoilOut[8] = "";

D4D_CHAR str_tarHltIn[8] = "";
D4D_CHAR str_tarHltOut[8] = "";
D4D_CHAR str_tarMashIn[8] = "";
D4D_CHAR str_tarMashOut[8] = "";
D4D_CHAR str_tarBoilIn[8] = "";
D4D_CHAR str_tarBoilInside[8] = "";
D4D_CHAR str_tarBoilOut[8] = "";


D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_Process,    "Process:",     5,  40, 100, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Current,   "Current",    130,  65,  70, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_darkgrey);
D4D_DECLARE_STD_LABEL_CENTER(scrBrew_Target,    "Target",     220,  65,  70, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_darkgrey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_HltIn,      "HLT In:",      5,  90,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_HltOut,     "HLT Out:",     5, 110,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_MashIn,     "Mash In:",     5, 135,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_MashOut,    "Mash Out:",    5, 155,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_BoilIn,     "Boil In:",     5, 180,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_BoilInside, "Boil Inside:", 5, 200,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_BoilOut,    "Boil Out:",    5, 220,  90, 20, FONT_ARIAL_11, (D4D_CLR_SCHEME*)&scheme_grey);

D4D_DECLARE_STD_LABEL(scrBrew_valProcess,       str_Process,       110,  40, 100, 20, FONT_ARIAL_11);

D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curHltIn,      str_curHltIn,      130,  90,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curHltOut,     str_curHltOut,     130, 110,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curMashIn,     str_curMashIn,     130, 135,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curMashOut,    str_curMashOut,    130, 155,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curBoilIn,     str_curBoilIn,     130, 180,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curBoilInside, str_curBoilInside, 130, 200,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_curBoilOut,    str_curBoilOut,    130, 220,  70, 20, FONT_ARIAL_11, NULL);

D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarHltIn,      str_tarHltIn,      220,  90,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarHltOut,     str_tarHltOut,     220, 110,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarMashIn,     str_tarMashIn,     220, 135,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarMashOut,    str_tarMashOut,    220, 155,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarBoilIn,     str_tarBoilIn,     220, 180,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarBoilInside, str_tarBoilInside, 220, 200,  70, 20, FONT_ARIAL_11, NULL);
D4D_DECLARE_STD_LABEL_RIGHT(scrBrew_tarBoilOut,    str_tarBoilOut,    220, 220,  70, 20, FONT_ARIAL_11, NULL);

        
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

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curHltIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curHltOut)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curMashIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curMashOut)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curBoilIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curBoilInside)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_curBoilOut)

    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarHltIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarHltOut)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarMashIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarMashOut)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarBoilIn)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarBoilInside)
    D4D_DECLARE_SCREEN_OBJECT(scrBrew_tarBoilOut)
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
