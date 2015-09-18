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

void updateLabel(D4D_OBJECT* pThis, D4D_CHAR* text);

    
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


#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_SCREEN_H */
