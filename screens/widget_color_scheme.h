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

#include <stdint.h>
#include "d4d.h"


#define INACTIVE_BG_COLOR D4D_COLOR_RGB(112,138,144)
#define ACTIVE_BG_COLOR D4D_COLOR_RGB(250,128,114)


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


#define D4D_DECLARE_FORE_SCHEME(name, fore) \
    D4D_DECLARE_CLR_SCHEME(name, \
        D4D_COLOR_SCR_DESKTOP, D4D_COLOR_SCR_OUTLINE, D4D_COLOR_SCR_TITLEBAR, D4D_COLOR_SCR_TILTLETEXT, D4D_COLOR_SCR_EXIT_BTN_FORE, D4D_COLOR_SCR_EXIT_BTN_BCKG,\
        D4D_COLOR_BCKG_NORM, D4D_COLOR_BCKG_DISABLED, D4D_COLOR_BCKG_FOCUS, D4D_COLOR_BCKG_CAPTURE,\
        fore, D4D_COLOR_FORE_DISABLED, D4D_COLOR_FORE_FOCUS, D4D_COLOR_FORE_CAPTURE,\
        D4D_COLOR_GAUG_HUB, D4D_COLOR_GAUG_POINTER,\
        D4D_COLOR_SLDR_BAR_BCKG, D4D_COLOR_SLDR_BAR_FORE, D4D_COLOR_SLDR_BAR_START, D4D_COLOR_SLDR_BAR_END,\
        D4D_COLOR_CHECKBOX_ICON_BCKG,\
        D4D_COLOR_GRAPH_GRID,\
        D4D_COLOR_PRGRS_BAR_BAR_BCKG, D4D_COLOR_PRGRS_BAR_BAR_FORE, D4D_COLOR_PRGRS_BAR_BAR_END \
    )


D4D_DECLARE_FORE_SCHEME(scheme_grey, D4D_COLOR_RGB(170,170,170));
D4D_DECLARE_FORE_SCHEME(scheme_darkgrey, D4D_COLOR_RGB(128,128,128));
D4D_DECLARE_FORE_SCHEME(scheme_red, D4D_COLOR_RED);
D4D_DECLARE_FORE_SCHEME(scheme_green, D4D_COLOR_GREEN);
            

#endif	/* WIDGET_COLOR_SCHEME_H */

