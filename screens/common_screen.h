/**
 ******************************************************************************
 * @file    common_screen.h
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


#ifndef COMMON_SCREEN_H
#define	COMMON_SCREEN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "fonts.h"
#include "widget_color_scheme.h"

void menuButtonClicked(D4D_OBJECT* pThis);
void changeMenuButtonState(D4D_OBJECT* pThis, D4D_BOOL state, D4D_CHAR* text);
void updateLabel(D4D_OBJECT* pThis, D4D_CHAR* text);

    
D4D_EXTERN_OBJECT(scr_btnInfo);
#ifdef CONFIG_BREW
D4D_EXTERN_OBJECT(scr_btnBrew);
#endif
#ifdef CONFIG_FERM
D4D_EXTERN_OBJECT(scr_btnFerm);
#endif

#define D4D_DECLARE_STD_LABEL_RIGHT(name, text, x, y, cx, cy, fontId, bg, fg) \
    static D4D_STR_PROPERTIES name##_strPrties = { D4D_LBL_FNT_PRTY_DEFAULT, D4D_LBL_TXT_PRTY_RIGHT}; \
    static D4D_CONST D4D_LABEL name##_params = \
    { \
        { text, D4D_TEXT_LEN(text), fontId, &name##_strPrties, D4D_OBJECT_MAX_TEXT_LEN(text), 0} /* textBuff */ \
    }; \
	WIDGET_COLOR_SCHEME name##_color = { bg, bg, bg, bg, fg, fg, fg, fg }; \
    D4D_DECLARE_OBJECT(D4D_CONST, name, x, y, cx, cy, 0, NULL, NULL, NULL, &d4d_labelSysFunc, &(name##_params), (D4D_LBL_F_DEFAULT), NULL, AS_D4D_COLOR_SCHEME(&name##_color))


#define D4D_DECLARE_STD_LABEL_CENTER(name, text, x, y, cx, cy, fontId, bg, fg) \
    static D4D_STR_PROPERTIES name##_strPrties = { D4D_LBL_FNT_PRTY_DEFAULT, D4D_LBL_TXT_PRTY_CENTER}; \
    static D4D_CONST D4D_LABEL name##_params = \
    { \
        { text, D4D_TEXT_LEN(text), fontId, &name##_strPrties, D4D_OBJECT_MAX_TEXT_LEN(text), 0} /* textBuff */ \
    }; \
    \
	WIDGET_COLOR_SCHEME name##_color = { bg, bg, bg, bg, fg, fg, fg, fg }; \
    D4D_DECLARE_OBJECT(D4D_CONST, name, x, y, cx, cy, 0, NULL, NULL, NULL, &d4d_labelSysFunc, &(name##_params), (D4D_LBL_F_DEFAULT), NULL, AS_D4D_COLOR_SCHEME(&name##_color))



#define D4D_DECLARE_MENU_BUTTON(name, x, y, cx, cy, fontId) \
    _D4D_DECLARE_MENU_BUTTON(scr_btn##name, name, x, y, cx, cy, fontId) \

#define _D4D_DECLARE_MENU_BUTTON(name, text, x, y, cx, cy, fontId) \
    char name##text[10] = ""; \
    D4D_CLR_SCHEME name##scheme; \
    _D4D_DECLARE_BUTTON(D4D_CONST, name, name##text, x, y, cx, cy, 0, NULL, NULL, (D4D_OBJECT_F_VISIBLE | D4D_OBJECT_F_ENABLED | D4D_OBJECT_F_TOUCHENABLE | D4D_OBJECT_F_FASTTOUCH ), NULL, NULL, &name##scheme, fontId, NULL, menuButtonClicked, NULL);



#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_SCREEN_H */
