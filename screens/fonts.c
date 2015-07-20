/**
 ******************************************************************************
 * @file    fonts.c
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


D4D_DECLARE_FONT_TABLE_BEGIN
D4D_DECLARE_FONT(FONT_ARIAL_11, d4dfnt_Arial_11_desc, 1, 1, 0, 0)
D4D_DECLARE_FONT(FONT_NUMBER_MEDIUM, d4dfnt_AlteDIN1451_16_desc, 1, 1, 0, 0)
D4D_DECLARE_FONT_TABLE_END


const Byte d4dfnt_Arial_11_data_table[] = { 

/* character 0x0020 (' '): (width = 4, offset = 0) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0028 ('('): (width = 5, offset = 9) */
0x00, 0x00, 0x22, 0x11, 0x08, 0x42, 0x10, 0x84, 0x30, 0x84, 0x10, 

/* character 0x0029 (')'): (width = 5, offset = 20) */
0x00, 0x00, 0x82, 0x10, 0x42, 0x10, 0x84, 0x21, 0x18, 0x84, 0x40, 

/* character 0x002E ('.'): (width = 4, offset = 31) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 

/* character 0x0030 ('0'): (width = 8, offset = 40) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0031 ('1'): (width = 8, offset = 57) */
0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
0x00, 

/* character 0x0032 ('2'): (width = 8, offset = 74) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 0x02, 0x04, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00, 0x00,
0x00, 

/* character 0x0033 ('3'): (width = 8, offset = 91) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 0x02, 0x1C, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0034 ('4'): (width = 8, offset = 108) */
0x00, 0x00, 0x00, 0x04, 0x0C, 0x14, 0x24, 0x24, 0x44, 0x84, 0xFE, 0x04, 0x04, 0x04, 0x00, 0x00,
0x00, 

/* character 0x0035 ('5'): (width = 8, offset = 125) */
0x00, 0x00, 0x00, 0x3E, 0x20, 0x20, 0x40, 0x7C, 0x42, 0x02, 0x02, 0x42, 0x44, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0036 ('6'): (width = 8, offset = 142) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0037 ('7'): (width = 8, offset = 159) */
0x00, 0x00, 0x00, 0x7E, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
0x00, 

/* character 0x0038 ('8'): (width = 8, offset = 176) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0039 ('9'): (width = 8, offset = 193) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x003A (':'): (width = 4, offset = 210) */
0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x00, 

/* character 0x0041 ('A'): (width = 9, offset = 219) */
0x00, 0x00, 0x00, 0x01, 0x01, 0x40, 0xA0, 0x50, 0x44, 0x22, 0x20, 0x9F, 0xC8, 0x28, 0x0C, 0x04,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0042 ('B'): (width = 10, offset = 239) */
0x00, 0x00, 0x00, 0x01, 0xFC, 0x40, 0x90, 0x24, 0x09, 0x04, 0x7F, 0x10, 0x24, 0x09, 0x02, 0x40,
0x9F, 0xC0, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0043 ('C'): (width = 11, offset = 261) */
0x00, 0x00, 0x00, 0x00, 0x07, 0x83, 0x08, 0x40, 0x90, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x10,
0x23, 0x08, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0044 ('D'): (width = 11, offset = 285) */
0x00, 0x00, 0x00, 0x00, 0x3F, 0x84, 0x08, 0x80, 0x90, 0x12, 0x02, 0x40, 0x48, 0x09, 0x01, 0x20,
0x24, 0x08, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0045 ('E'): (width = 10, offset = 309) */
0x00, 0x00, 0x00, 0x01, 0xFE, 0x40, 0x10, 0x04, 0x01, 0x00, 0x7F, 0x90, 0x04, 0x01, 0x00, 0x40,
0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0046 ('F'): (width = 9, offset = 331) */
0x00, 0x00, 0x00, 0x0F, 0xE4, 0x02, 0x01, 0x00, 0x80, 0x7E, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0047 ('G'): (width = 11, offset = 351) */
0x00, 0x00, 0x00, 0x00, 0x0F, 0x82, 0x08, 0x80, 0x90, 0x02, 0x00, 0x43, 0xC8, 0x09, 0x01, 0x20,
0x22, 0x08, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0048 ('H'): (width = 10, offset = 375) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x90, 0x24, 0x09, 0x02, 0x7F, 0x90, 0x24, 0x09, 0x02, 0x40,
0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0049 ('I'): (width = 3, offset = 397) */
0x00, 0x24, 0x92, 0x49, 0x24, 0x80, 0x00, 

/* character 0x004A ('J'): (width = 7, offset = 404) */
0x00, 0x00, 0x00, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x14, 0x28, 0x4F, 0x00, 0x00, 0x00, 

/* character 0x004B ('K'): (width = 10, offset = 419) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x41, 0x10, 0x84, 0x41, 0x20, 0x54, 0x18, 0x84, 0x21, 0x04, 0x40,
0x90, 0x10, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004C ('L'): (width = 8, offset = 441) */
0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x00, 0x00,
0x00, 

/* character 0x004D ('M'): (width = 11, offset = 458) */
0x00, 0x00, 0x00, 0x00, 0x20, 0x26, 0x0C, 0xC1, 0x94, 0x52, 0x8A, 0x51, 0x49, 0x49, 0x29, 0x25,
0x24, 0x44, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004E ('N'): (width = 10, offset = 482) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x60, 0x94, 0x25, 0x09, 0x22, 0x48, 0x91, 0x24, 0x29, 0x0A, 0x41,
0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004F ('O'): (width = 12, offset = 504) */
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x30, 0xC2, 0x04, 0x40, 0x24, 0x02, 0x40, 0x24, 0x02, 0x40,
0x22, 0x04, 0x30, 0xC0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0050 ('P'): (width = 10, offset = 530) */
0x00, 0x00, 0x00, 0x01, 0xFC, 0x40, 0x90, 0x24, 0x09, 0x02, 0x7F, 0x10, 0x04, 0x01, 0x00, 0x40,
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0051 ('Q'): (width = 12, offset = 552) */
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x30, 0xC2, 0x04, 0x40, 0x24, 0x02, 0x40, 0x24, 0x02, 0x40,
0x22, 0x34, 0x30, 0xC0, 0xF2, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0052 ('R'): (width = 11, offset = 578) */
0x00, 0x00, 0x00, 0x00, 0x3F, 0xC4, 0x04, 0x80, 0x90, 0x12, 0x02, 0x7F, 0x88, 0x41, 0x04, 0x20,
0x84, 0x08, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0053 ('S'): (width = 10, offset = 602) */
0x00, 0x00, 0x00, 0x00, 0x78, 0x21, 0x10, 0x24, 0x01, 0xE0, 0x07, 0x00, 0x20, 0x09, 0x02, 0x61,
0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0054 ('T'): (width = 9, offset = 624) */
0x00, 0x00, 0x00, 0x1F, 0xF0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x80, 0x40,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0055 ('U'): (width = 10, offset = 644) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x90, 0x24, 0x09, 0x02, 0x40, 0x90, 0x24, 0x09, 0x02, 0x21,
0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0056 ('V'): (width = 9, offset = 666) */
0x00, 0x00, 0x00, 0x10, 0x18, 0x0A, 0x09, 0x04, 0x44, 0x22, 0x11, 0x05, 0x02, 0x80, 0x80, 0x40,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0057 ('W'): (width = 15, offset = 686) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x18, 0x28, 0x28, 0x50, 0x90, 0xA1, 0x22, 0x22, 0x44,
0x44, 0x48, 0x90, 0xA0, 0xA1, 0x41, 0x41, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,


/* character 0x0058 ('X'): (width = 9, offset = 718) */
0x00, 0x00, 0x00, 0x10, 0x14, 0x11, 0x10, 0x88, 0x28, 0x08, 0x0A, 0x08, 0x84, 0x44, 0x14, 0x04,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0059 ('Y'): (width = 9, offset = 738) */
0x00, 0x00, 0x00, 0x10, 0x14, 0x11, 0x10, 0x88, 0x28, 0x08, 0x04, 0x02, 0x01, 0x00, 0x80, 0x40,
0x00, 0x00, 0x00, 0x00, 

/* character 0x005A ('Z'): (width = 8, offset = 758) */
0x00, 0x00, 0x00, 0x7F, 0x02, 0x04, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0xFF, 0x00, 0x00,
0x00, 

/* character 0x0061 ('a'): (width = 8, offset = 775) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x02, 0x1E, 0x22, 0x42, 0x46, 0x3A, 0x00, 0x00,
0x00, 

/* character 0x0062 ('b'): (width = 8, offset = 792) */
0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x00, 0x00,
0x00, 

/* character 0x0063 ('c'): (width = 8, offset = 809) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0064 ('d'): (width = 8, offset = 826) */
0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00,
0x00, 

/* character 0x0065 ('e'): (width = 8, offset = 843) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0066 ('f'): (width = 4, offset = 860) */
0x00, 0x03, 0x44, 0xF4, 0x44, 0x44, 0x44, 0x00, 0x00, 

/* character 0x0067 ('g'): (width = 8, offset = 869) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x42,
0x3C, 

/* character 0x0068 ('h'): (width = 8, offset = 886) */
0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
0x00, 

/* character 0x0069 ('i'): (width = 3, offset = 903) */
0x00, 0x20, 0x12, 0x49, 0x24, 0x80, 0x00, 

/* character 0x006A ('j'): (width = 3, offset = 910) */
0x00, 0x20, 0x12, 0x49, 0x24, 0x92, 0x80, 

/* character 0x006B ('k'): (width = 7, offset = 917) */
0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0xA2, 0x48, 0xA1, 0xA2, 0x24, 0x48, 0x40, 0x00, 0x00, 

/* character 0x006C ('l'): (width = 3, offset = 932) */
0x00, 0x24, 0x92, 0x49, 0x24, 0x80, 0x00, 

/* character 0x006D ('m'): (width = 13, offset = 939) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x73, 0x8C, 0x62, 0x42, 0x12, 0x10,
0x90, 0x84, 0x84, 0x24, 0x21, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x006E ('n'): (width = 8, offset = 967) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
0x00, 

/* character 0x006F ('o'): (width = 8, offset = 984) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0070 ('p'): (width = 8, offset = 1001) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40,
0x40, 

/* character 0x0071 ('q'): (width = 8, offset = 1018) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x02,
0x02, 

/* character 0x0072 ('r'): (width = 5, offset = 1035) */
0x00, 0x00, 0x00, 0x01, 0x6C, 0x42, 0x10, 0x84, 0x20, 0x00, 0x00, 

/* character 0x0073 ('s'): (width = 8, offset = 1046) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x40, 0x30, 0x0C, 0x02, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0074 ('t'): (width = 4, offset = 1063) */
0x00, 0x00, 0x44, 0xF4, 0x44, 0x44, 0x47, 0x00, 0x00, 

/* character 0x0075 ('u'): (width = 8, offset = 1072) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00,
0x00, 

/* character 0x0076 ('v'): (width = 7, offset = 1089) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xC1, 0x44, 0x88, 0xA1, 0x41, 0x02, 0x00, 0x00, 0x00, 

/* character 0x0077 ('w'): (width = 11, offset = 1104) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x0C, 0x51, 0x4A, 0x49, 0x49, 0x45, 0x28,
0xA2, 0x08, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0078 ('x'): (width = 7, offset = 1128) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xA2, 0x28, 0x20, 0x41, 0x44, 0x50, 0x40, 0x00, 0x00, 

/* character 0x0079 ('y'): (width = 7, offset = 1143) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xC1, 0x44, 0x88, 0xA1, 0x42, 0x82, 0x04, 0x08, 0x60, 

/* character 0x007A ('z'): (width = 8, offset = 1158) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x7E, 0x00, 0x00,
0x00

};

const D4D_FONT_OFFSET d4dfnt_Arial_11_offset_table[] = { 

/*       offset       char      hexcode     */
/*       ======      =====      =======     */
            0,    /*   ' '        0020       */
            9,    /*   '('        0028       */
           20,    /*   ')'        0029       */
           31,    /*   '.'        002E       */
           40,    /*   '0'        0030       */
           57,    /*   '1'        0031       */
           74,    /*   '2'        0032       */
           91,    /*   '3'        0033       */
          108,    /*   '4'        0034       */
          125,    /*   '5'        0035       */
          142,    /*   '6'        0036       */
          159,    /*   '7'        0037       */
          176,    /*   '8'        0038       */
          193,    /*   '9'        0039       */
          210,    /*   ':'        003A       */
          219,    /*   'A'        0041       */
          239,    /*   'B'        0042       */
          261,    /*   'C'        0043       */
          285,    /*   'D'        0044       */
          309,    /*   'E'        0045       */
          331,    /*   'F'        0046       */
          351,    /*   'G'        0047       */
          375,    /*   'H'        0048       */
          397,    /*   'I'        0049       */
          404,    /*   'J'        004A       */
          419,    /*   'K'        004B       */
          441,    /*   'L'        004C       */
          458,    /*   'M'        004D       */
          482,    /*   'N'        004E       */
          504,    /*   'O'        004F       */
          530,    /*   'P'        0050       */
          552,    /*   'Q'        0051       */
          578,    /*   'R'        0052       */
          602,    /*   'S'        0053       */
          624,    /*   'T'        0054       */
          644,    /*   'U'        0055       */
          666,    /*   'V'        0056       */
          686,    /*   'W'        0057       */
          718,    /*   'X'        0058       */
          738,    /*   'Y'        0059       */
          758,    /*   'Z'        005A       */
          775,    /*   'a'        0061       */
          792,    /*   'b'        0062       */
          809,    /*   'c'        0063       */
          826,    /*   'd'        0064       */
          843,    /*   'e'        0065       */
          860,    /*   'f'        0066       */
          869,    /*   'g'        0067       */
          886,    /*   'h'        0068       */
          903,    /*   'i'        0069       */
          910,    /*   'j'        006A       */
          917,    /*   'k'        006B       */
          932,    /*   'l'        006C       */
          939,    /*   'm'        006D       */
          967,    /*   'n'        006E       */
          984,    /*   'o'        006F       */
         1001,    /*   'p'        0070       */
         1018,    /*   'q'        0071       */
         1035,    /*   'r'        0072       */
         1046,    /*   's'        0073       */
         1063,    /*   't'        0074       */
         1072,    /*   'u'        0075       */
         1089,    /*   'v'        0076       */
         1104,    /*   'w'        0077       */
         1128,    /*   'x'        0078       */
         1143,    /*   'y'        0079       */
         1158    /*   'z'        007A       */
};

const D4D_FONT_IX d4dfnt_Arial_11_index_table[] = { 

/*        char      hexacode      decimal       index     */
/*       ======     ========      =======      =======    */
          ' ',    /*   0020          32            0       */
          '(',    /*   0028          40            1       */
          ')',    /*   0029          41            2       */
          '.',    /*   002E          46            3       */
          '0',    /*   0030          48            4       */
          '1',    /*   0031          49            5       */
          '2',    /*   0032          50            6       */
          '3',    /*   0033          51            7       */
          '4',    /*   0034          52            8       */
          '5',    /*   0035          53            9       */
          '6',    /*   0036          54           10       */
          '7',    /*   0037          55           11       */
          '8',    /*   0038          56           12       */
          '9',    /*   0039          57           13       */
          ':',    /*   003A          58           14       */
          'A',    /*   0041          65           15       */
          'B',    /*   0042          66           16       */
          'C',    /*   0043          67           17       */
          'D',    /*   0044          68           18       */
          'E',    /*   0045          69           19       */
          'F',    /*   0046          70           20       */
          'G',    /*   0047          71           21       */
          'H',    /*   0048          72           22       */
          'I',    /*   0049          73           23       */
          'J',    /*   004A          74           24       */
          'K',    /*   004B          75           25       */
          'L',    /*   004C          76           26       */
          'M',    /*   004D          77           27       */
          'N',    /*   004E          78           28       */
          'O',    /*   004F          79           29       */
          'P',    /*   0050          80           30       */
          'Q',    /*   0051          81           31       */
          'R',    /*   0052          82           32       */
          'S',    /*   0053          83           33       */
          'T',    /*   0054          84           34       */
          'U',    /*   0055          85           35       */
          'V',    /*   0056          86           36       */
          'W',    /*   0057          87           37       */
          'X',    /*   0058          88           38       */
          'Y',    /*   0059          89           39       */
          'Z',    /*   005A          90           40       */
          'a',    /*   0061          97           41       */
          'b',    /*   0062          98           42       */
          'c',    /*   0063          99           43       */
          'd',    /*   0064         100           44       */
          'e',    /*   0065         101           45       */
          'f',    /*   0066         102           46       */
          'g',    /*   0067         103           47       */
          'h',    /*   0068         104           48       */
          'i',    /*   0069         105           49       */
          'j',    /*   006A         106           50       */
          'k',    /*   006B         107           51       */
          'l',    /*   006C         108           52       */
          'm',    /*   006D         109           53       */
          'n',    /*   006E         110           54       */
          'o',    /*   006F         111           55       */
          'p',    /*   0070         112           56       */
          'q',    /*   0071         113           57       */
          'r',    /*   0072         114           58       */
          's',    /*   0073         115           59       */
          't',    /*   0074         116           60       */
          'u',    /*   0075         117           61       */
          'v',    /*   0076         118           62       */
          'w',    /*   0077         119           63       */
          'x',    /*   0078         120           64       */
          'y',    /*   0079         121           65       */
          'z'    /*   007A         122           66       */
};

const D4D_FONT_SIZE d4dfnt_Arial_11_width_table[] = { 

/*       width        char      hexcode     */
/*       ======      =====      =======     */
           4,    /*   ' '        0020       */
           5,    /*   '('        0028       */
           5,    /*   ')'        0029       */
           4,    /*   '.'        002E       */
           8,    /*   '0'        0030       */
           8,    /*   '1'        0031       */
           8,    /*   '2'        0032       */
           8,    /*   '3'        0033       */
           8,    /*   '4'        0034       */
           8,    /*   '5'        0035       */
           8,    /*   '6'        0036       */
           8,    /*   '7'        0037       */
           8,    /*   '8'        0038       */
           8,    /*   '9'        0039       */
           4,    /*   ':'        003A       */
           9,    /*   'A'        0041       */
          10,    /*   'B'        0042       */
          11,    /*   'C'        0043       */
          11,    /*   'D'        0044       */
          10,    /*   'E'        0045       */
           9,    /*   'F'        0046       */
          11,    /*   'G'        0047       */
          10,    /*   'H'        0048       */
           3,    /*   'I'        0049       */
           7,    /*   'J'        004A       */
          10,    /*   'K'        004B       */
           8,    /*   'L'        004C       */
          11,    /*   'M'        004D       */
          10,    /*   'N'        004E       */
          12,    /*   'O'        004F       */
          10,    /*   'P'        0050       */
          12,    /*   'Q'        0051       */
          11,    /*   'R'        0052       */
          10,    /*   'S'        0053       */
           9,    /*   'T'        0054       */
          10,    /*   'U'        0055       */
           9,    /*   'V'        0056       */
          15,    /*   'W'        0057       */
           9,    /*   'X'        0058       */
           9,    /*   'Y'        0059       */
           8,    /*   'Z'        005A       */
           8,    /*   'a'        0061       */
           8,    /*   'b'        0062       */
           8,    /*   'c'        0063       */
           8,    /*   'd'        0064       */
           8,    /*   'e'        0065       */
           4,    /*   'f'        0066       */
           8,    /*   'g'        0067       */
           8,    /*   'h'        0068       */
           3,    /*   'i'        0069       */
           3,    /*   'j'        006A       */
           7,    /*   'k'        006B       */
           3,    /*   'l'        006C       */
          13,    /*   'm'        006D       */
           8,    /*   'n'        006E       */
           8,    /*   'o'        006F       */
           8,    /*   'p'        0070       */
           8,    /*   'q'        0071       */
           5,    /*   'r'        0072       */
           8,    /*   's'        0073       */
           4,    /*   't'        0074       */
           8,    /*   'u'        0075       */
           7,    /*   'v'        0076       */
          11,    /*   'w'        0077       */
           7,    /*   'x'        0078       */
           7,    /*   'y'        0079       */
           8     /*   'z'        007A       */
};

const D4D_FONT_DESCRIPTOR d4dfnt_Arial_11_desc = {
    0,       // Font descriptor version number
    D4D_FONT_FLAGS_IX_STYLE_NONLINEAR | D4D_FONT_FLAGS_IX_TYPE_MAP | D4D_FONT_FLAGS_FNT_WIDTH_PROPORTIONAL,   // linear / nonlinear , proporcional or not
    ' ',     // start char of used table
    67,   // count of all chars of used table
    0x0020,     // index of char that will be printed instead of
    11,       // font size (size of font loaded in PC)
    0,     // height of font bitmpap for non proporcional fonts
    14,      // offset from Y0 coordination to baseline
    {15, 17},     // size of biggest char x/y
    D4D_FONT_PACK_BITORDER_BIGEND | D4D_FONT_PACK_SCANBASED_ROW | D4D_FONT_PACK_SCANPREFERRED_ROW | D4D_FONT_PACK_COMPRESSED_ON,     // packing condition of individual bitmaps
    d4dfnt_Arial_11_index_table,          // Index table - is used when nonlinearIX is set in flags, flags also determine the type of IxTable
    d4dfnt_Arial_11_offset_table,     // Offset table - used when proporcial font is set in flags
    d4dfnt_Arial_11_width_table,        // Size table - used when proporcial font is set in flags
    d4dfnt_Arial_11_data_table,      // bitmap/font data array
    NULL       // pointer for next UNICODE page
};


const Byte d4dfnt_AlteDIN1451_16_data_table[] = {

/* character 0x002B ('+'): (width = 13, offset = 0) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x03, 0x00, 0x18, 0x00, 0xC0, 0x06, 0x07, 0xFF,
0x3F, 0xF8, 0x0C, 0x00, 0x60, 0x03, 0x00, 0x18, 0x00,

/* character 0x002D ('-'): (width = 9, offset = 25) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00,

/* character 0x002E ('.'): (width = 5, offset = 42) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xC0,

/* character 0x0030 ('0'): (width = 10, offset = 52) */
0x1E, 0x0F, 0xC7, 0x39, 0x86, 0x61, 0x98, 0x66, 0x19, 0x86, 0x61, 0x98, 0x66, 0x19, 0x86, 0x73,
0x8F, 0xC1, 0xE0,

/* character 0x0031 ('1'): (width = 7, offset = 71) */
0x1C, 0x78, 0xF1, 0x60, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0x00,

/* character 0x0032 ('2'): (width = 10, offset = 85) */
0x1E, 0x0F, 0xC7, 0x19, 0x86, 0x01, 0x80, 0x60, 0x30, 0x1C, 0x0E, 0x03, 0x01, 0x80, 0xC0, 0x70,
0x1F, 0xE7, 0xF8,

/* character 0x0033 ('3'): (width = 10, offset = 104) */
0x1E, 0x0F, 0xC7, 0x39, 0x86, 0x01, 0x80, 0xE0, 0xF0, 0x3C, 0x03, 0x80, 0x60, 0x19, 0x86, 0x73,
0x8F, 0xC1, 0xE0,

/* character 0x0034 ('4'): (width = 10, offset = 123) */
0x03, 0x01, 0x80, 0x60, 0x30, 0x0C, 0x07, 0x01, 0x80, 0xE6, 0x31, 0x9C, 0x66, 0x19, 0xFF, 0x7F,
0xC0, 0x60, 0x18,

/* character 0x0035 ('5'): (width = 10, offset = 142) */
0x7F, 0x9F, 0xE6, 0x01, 0x80, 0x60, 0x1F, 0x87, 0xF1, 0xC6, 0x01, 0x80, 0x60, 0x19, 0x86, 0x71,
0x8F, 0xC1, 0xE0,

/* character 0x0036 ('6'): (width = 10, offset = 161) */
0x1E, 0x0F, 0xC7, 0x39, 0x80, 0x60, 0x1F, 0x87, 0xF1, 0xCE, 0x61, 0x98, 0x66, 0x19, 0x86, 0x73,
0x8F, 0xC1, 0xE0,

/* character 0x0037 ('7'): (width = 10, offset = 180) */
0x7F, 0x9F, 0xE6, 0x19, 0x8E, 0x03, 0x00, 0xC0, 0x70, 0x18, 0x0E, 0x03, 0x80, 0xC0, 0x70, 0x18,
0x06, 0x03, 0x80,

/* character 0x0038 ('8'): (width = 10, offset = 199) */
0x1E, 0x0F, 0xC7, 0x19, 0x86, 0x61, 0x9C, 0x63, 0xF0, 0xFC, 0x73, 0x98, 0x66, 0x19, 0x86, 0x73,
0x8F, 0xC1, 0xE0,

/* character 0x0039 ('9'): (width = 10, offset = 218) */
0x1E, 0x0F, 0xC7, 0x39, 0x86, 0x61, 0x98, 0x66, 0x19, 0xCE, 0x3F, 0x87, 0xE0, 0x18, 0x06, 0x63,
0x8F, 0xC1, 0xE0,

/* character 0x0043 ('C'): (width = 12, offset = 237) */
0x0F, 0x03, 0xFC, 0x30, 0xC6, 0x0E, 0x60, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60,
0x06, 0x0E, 0x31, 0xE3, 0xFC, 0x0F, 0x00,

/* character 0x0046 ('F'): (width = 11, offset = 260) */
0x3F, 0xE7, 0xFC, 0xC0, 0x18, 0x03, 0x00, 0x60, 0x0C, 0x01, 0xFE, 0x3F, 0xC6, 0x00, 0xC0, 0x18,
0x03, 0x00, 0x60, 0x0C, 0x00,

/* character 0x00B0 (' '): (width = 7, offset = 281) */
0x79, 0x8A, 0x14, 0x2C, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

/* character 0x0020 (' '): (width = 9, offset = 295) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00

};

const D4D_FONT_OFFSET d4dfnt_AlteDIN1451_16_offset_table[] = {

/*       offset       char      hexcode     */
/*       ======      =====      =======     */
            0,    /*   '+'        002B       */
           25,    /*   '-'        002D       */
           42,    /*   '.'        002E       */
           52,    /*   '0'        0030       */
           71,    /*   '1'        0031       */
           85,    /*   '2'        0032       */
          104,    /*   '3'        0033       */
          123,    /*   '4'        0034       */
          142,    /*   '5'        0035       */
          161,    /*   '6'        0036       */
          180,    /*   '7'        0037       */
          199,    /*   '8'        0038       */
          218,    /*   '9'        0039       */
          237,    /*   'C'        0043       */
          260,    /*   'F'        0046       */
          281,    /*   ' '        00B0       */
		  295     /*   ' '        0020       */
};

const D4D_FONT_IX d4dfnt_AlteDIN1451_16_index_table[] = {

/*        char      hexacode      decimal       index     */
/*       ======     ========      =======      =======    */
          '+',    /*   002B          43            0       */
          '-',    /*   002D          45            1       */
          '.',    /*   002E          46            2       */
          '0',    /*   0030          48            3       */
          '1',    /*   0031          49            4       */
          '2',    /*   0032          50            5       */
          '3',    /*   0033          51            6       */
          '4',    /*   0034          52            7       */
          '5',    /*   0035          53            8       */
          '6',    /*   0036          54            9       */
          '7',    /*   0037          55           10       */
          '8',    /*   0038          56           11       */
          '9',    /*   0039          57           12       */
          'C',    /*   0043          67           13       */
          'F',    /*   0046          70           14       */
         0x00B0,  /*   00B0         176           15       */
		  ' '     /*   0020          32           16       */
};

const D4D_FONT_SIZE d4dfnt_AlteDIN1451_16_width_table[] = {

/*       width        char      hexcode     */
/*       ======      =====      =======     */
          13,    /*   '+'        002B       */
           9,    /*   '-'        002D       */
           5,    /*   '.'        002E       */
          10,    /*   '0'        0030       */
           7,    /*   '1'        0031       */
          10,    /*   '2'        0032       */
          10,    /*   '3'        0033       */
          10,    /*   '4'        0034       */
          10,    /*   '5'        0035       */
          10,    /*   '6'        0036       */
          10,    /*   '7'        0037       */
          10,    /*   '8'        0038       */
          10,    /*   '9'        0039       */
          12,    /*   'C'        0043       */
          11,    /*   'F'        0046       */
           7,    /*   ' '        00B0       */
		   9     /*   ' '        0020       */
};

const D4D_FONT_DESCRIPTOR d4dfnt_AlteDIN1451_16_desc = {
    0,       // Font descriptor version number
    D4D_FONT_FLAGS_IX_STYLE_NONLINEAR | D4D_FONT_FLAGS_IX_TYPE_MAP | D4D_FONT_FLAGS_FNT_WIDTH_PROPORTIONAL,   // linear / nonlinear , proporcional or not
    '+',     // start char of used table
    17,      // count of all chars of used table
    0x0020,  // index of char that will be printed instead of
    16,      // font size (size of font loaded in PC)
    0,       // height of font bitmpap for non proporcional fonts
    15,      // offset from Y0 coordination to baseline
    {13, 15},     // size of biggest char x/y
    D4D_FONT_PACK_BITORDER_BIGEND | D4D_FONT_PACK_SCANBASED_ROW | D4D_FONT_PACK_SCANPREFERRED_ROW | D4D_FONT_PACK_COMPRESSED_ON,     // packing condition of individual bitmaps
    d4dfnt_AlteDIN1451_16_index_table,          // Index table - is used when nonlinearIX is set in flags, flags also determine the type of IxTable
    d4dfnt_AlteDIN1451_16_offset_table,     // Offset table - used when proporcial font is set in flags
    d4dfnt_AlteDIN1451_16_width_table,        // Size table - used when proporcial font is set in flags
    d4dfnt_AlteDIN1451_16_data_table,      // bitmap/font data array
    NULL      // pointer for next UNICODE page
};
