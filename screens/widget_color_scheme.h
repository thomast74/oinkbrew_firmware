/**
 ******************************************************************************
 * @file    widget_color_scheme.h
 * @authors mat
 * @date    27 February 2015
 ******************************************************************************
  Copyright (c) 2015 Brewpi.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

#ifndef WIDGET_COLOR_SCHEME_H
#define	WIDGET_COLOR_SCHEME_H

#include <stddef.h>
#include <stdint.h>
#include "d4d.h"

#define INACTIVE_BG_COLOR D4D_COLOR_RGB(112,138,144)
#define ACTIVE_BG_COLOR D4D_COLOR_RGB(250,128,114)

#define OINK_COLOR_GREY         D4D_COLOR_RGB(170,170,170)
#define OINK_COLOR_DARKGREY     D4D_COLOR_RGB(128,128,128)
#define OINK_COLOR_RED          D4D_COLOR_RGB(0xb4, 0x00, 0x00)
#define OINK_COLOR_GREEN        D4D_COLOR_RGB(0xb3, 0x98, 0x00)
#define OINK_COLOR_BLUE         D4D_COLOR_RGB(0x00, 0x4b, 0xb4)


/**
 * The core colors for a simple widget. Most widgets use only these core color values
 * so we don't need to waste space storing the full D4D_COLOR_SCHEME which stores colors
 * that aren't applicable (screen, progress bar, guage etc...) 
 */
typedef struct WIDGET_COLOR_SCHEME {
  D4D_COLOR bckg;                       ///< The object background color in standard state
  D4D_COLOR bckgDis;                    ///< The object background color in disabled state
  D4D_COLOR bckgFocus;                  ///< The object background color in focused state
  D4D_COLOR bckgCapture;                ///< The object background color in captured state
  D4D_COLOR fore;                       ///< The object fore color in standard state
  D4D_COLOR foreDis;                    ///< The object fore color in disabled state
  D4D_COLOR foreFocus;                  ///< The object fore color in focused state
  D4D_COLOR foreCapture;                ///< The object fore color in captured state
} WIDGET_COLOR_SCHEME;

#define AS_D4D_COLOR_SCHEME(c) \
    ((D4D_CLR_SCHEME*)(((uint8_t*)c)-offsetof(D4D_CLR_SCHEME, bckg)))

#define D4D_DECLARE_COLOR_LABEL(name, text, x, y, cx, cy, font, type, bg, fg) \
    WIDGET_COLOR_SCHEME name##_color = { bg, bg, bg, bg, fg, fg, fg, fg }; \
    D4D_DECLARE_LABEL(name, text, x, y, cx, cy, D4D_LBL_F_DEFAULT, AS_D4D_COLOR_SCHEME(&name##_color), font, NULL, NULL);
            

#endif	/* WIDGET_COLOR_SCHEME_H */

