/**
 ******************************************************************************
 * @file    fonts.h
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


#ifndef FONTS_H
#define FONTS_H

#define FONT_ARIAL7    0
#define FONT_ARIAL7_HIGH     1 
#define FONT_ARIAL7_WIDE     2
#define FONT_ARIAL7_BIG      3
#define FONT_BERLIN_SANS_FBDEMI12         4
#define FONT_BERLIN_SANS_FBDEMI12_HIGH    5
#define FONT_BERLIN_SANS_FBDEMI12_BIG     6

extern const D4D_FONT_DESCRIPTOR d4dfnt_CourierNew8B_desc;
extern const D4D_FONT_DESCRIPTOR d4dfnt_TimesNewRoman12B_desc;
extern const D4D_FONT_DESCRIPTOR d4dfnt_BerlinSansFBDemi12_desc;
extern const D4D_FONT_DESCRIPTOR d4dfnt_Arial7_desc;
extern const D4D_FONT_DESCRIPTOR d4dfnt_CourierNewTest_desc;
#endif