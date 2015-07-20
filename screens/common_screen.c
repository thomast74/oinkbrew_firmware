/**
 ******************************************************************************
 * @file    common_screen.c
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
#include "common_screen.h"


D4D_DECLARE_MENU_BUTTON(Info,    5, 0, 70, 35, FONT_ARIAL_11);
D4D_DECLARE_MENU_BUTTON(Brew,   85, 0, 70, 35, FONT_ARIAL_11);
D4D_DECLARE_MENU_BUTTON(Ferm,  165, 0, 70, 35, FONT_ARIAL_11);


#define INACTIVE_BG_COLOR D4D_COLOR_RGB(112,138,144)
#define ACTIVE_BG_COLOR D4D_COLOR_RGB(250,128,114)


const WIDGET_COLOR_SCHEME color_scheme_menu_button = {
    ACTIVE_BG_COLOR,            // background active
    INACTIVE_BG_COLOR,          // background inactive
    D4D_COLOR_RGB(216,216,216), // foreground active
    D4D_COLOR_RGB(192,192,192), // foreground inactive
};


void changeMenuButtonState(D4D_OBJECT* pThis, D4D_BOOL state, D4D_CHAR* text)
{
    D4D_SetText(pThis, text);
    D4D_COLOR bg = state ? color_scheme_menu_button.bckg : color_scheme_menu_button.bckgDis;
    D4D_COLOR fg = state ? color_scheme_menu_button.fore : color_scheme_menu_button.foreDis;
    
    pThis->clrScheme->bckg = bg;
    pThis->clrScheme->bckgDis = bg;
    pThis->clrScheme->bckgCapture = bg;
    pThis->clrScheme->bckgFocus = bg;
    pThis->clrScheme->fore = fg;
    pThis->clrScheme->foreDis = fg;
    pThis->clrScheme->foreCapture = fg;
    pThis->clrScheme->foreFocus = fg;

    D4D_InvalidateObject(pThis, D4D_TRUE);
}

void updateLabel(D4D_OBJECT* pThis, D4D_CHAR* text)
{
    D4D_SetText(pThis, text);    
    D4D_InvalidateObject(pThis, D4D_TRUE);
}
