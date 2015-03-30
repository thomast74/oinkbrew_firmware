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
D4D_DECLARE_FONT(FONT_ARIAL_10, d4dfnt_Arial_10_desc, 1, 1, 0, 0)
D4D_DECLARE_FONT(FONT_ARIAL_11, d4dfnt_Arial_11_desc, 1, 1, 0, 0)
D4D_DECLARE_FONT_TABLE_END


const Byte d4dfnt_Arial_10_data_table[] = { 

/* character 0x0020 (' '): (width = 4, offset = 0) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x002B ('+'): (width = 8, offset = 8) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x7F, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,


/* character 0x002D ('-'): (width = 4, offset = 24) */
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 

/* character 0x002E ('.'): (width = 4, offset = 32) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 

/* character 0x0030 ('0'): (width = 7, offset = 40) */
0x00, 0x00, 0x03, 0xC8, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 0x27, 0x80, 0x00, 0x00, 

/* character 0x0031 ('1'): (width = 7, offset = 54) */
0x00, 0x00, 0x00, 0x83, 0x0A, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x00, 0x00, 0x00, 

/* character 0x0032 ('2'): (width = 7, offset = 68) */
0x00, 0x00, 0x03, 0xC8, 0x40, 0x81, 0x02, 0x08, 0x20, 0x82, 0x0F, 0xC0, 0x00, 0x00, 

/* character 0x0033 ('3'): (width = 7, offset = 82) */
0x00, 0x00, 0x03, 0xC8, 0x40, 0x81, 0x1C, 0x04, 0x08, 0x14, 0x27, 0x80, 0x00, 0x00, 

/* character 0x0034 ('4'): (width = 7, offset = 96) */
0x00, 0x00, 0x00, 0x41, 0x83, 0x0A, 0x14, 0x48, 0x93, 0xF0, 0x40, 0x80, 0x00, 0x00, 

/* character 0x0035 ('5'): (width = 7, offset = 110) */
0x00, 0x00, 0x03, 0xE4, 0x08, 0x20, 0x7C, 0x84, 0x08, 0x14, 0x27, 0x80, 0x00, 0x00, 

/* character 0x0036 ('6'): (width = 7, offset = 124) */
0x00, 0x00, 0x03, 0xC8, 0x50, 0x20, 0x5C, 0xC5, 0x0A, 0x14, 0x27, 0x80, 0x00, 0x00, 

/* character 0x0037 ('7'): (width = 7, offset = 138) */
0x00, 0x00, 0x07, 0xE0, 0x81, 0x04, 0x08, 0x20, 0x41, 0x02, 0x04, 0x00, 0x00, 0x00, 

/* character 0x0038 ('8'): (width = 7, offset = 152) */
0x00, 0x00, 0x03, 0xC8, 0x50, 0xA1, 0x3C, 0x85, 0x0A, 0x14, 0x27, 0x80, 0x00, 0x00, 

/* character 0x0039 ('9'): (width = 7, offset = 166) */
0x00, 0x00, 0x03, 0xC8, 0x50, 0xA1, 0x46, 0x74, 0x08, 0x14, 0x47, 0x00, 0x00, 0x00, 

/* character 0x003A (':'): (width = 4, offset = 180) */
0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 

/* character 0x0041 ('A'): (width = 9, offset = 188) */
0x00, 0x00, 0x00, 0x01, 0x01, 0x40, 0xA0, 0x50, 0x44, 0x22, 0x3F, 0x90, 0x50, 0x18, 0x08, 0x00,
0x00, 0x00, 

/* character 0x0042 ('B'): (width = 9, offset = 206) */
0x00, 0x00, 0x00, 0x0F, 0xC4, 0x12, 0x09, 0x04, 0xFC, 0x41, 0x20, 0x90, 0x48, 0x27, 0xE0, 0x00,
0x00, 0x00, 

/* character 0x0043 ('C'): (width = 9, offset = 224) */
0x00, 0x00, 0x00, 0x03, 0x82, 0x22, 0x09, 0x00, 0x80, 0x40, 0x20, 0x10, 0x44, 0x41, 0xC0, 0x00,
0x00, 0x00, 

/* character 0x0044 ('D'): (width = 9, offset = 242) */
0x00, 0x00, 0x00, 0x0F, 0x84, 0x22, 0x09, 0x04, 0x82, 0x41, 0x20, 0x90, 0x48, 0x47, 0xC0, 0x00,
0x00, 0x00, 

/* character 0x0045 ('E'): (width = 9, offset = 260) */
0x00, 0x00, 0x00, 0x0F, 0xE4, 0x02, 0x01, 0x00, 0xFE, 0x40, 0x20, 0x10, 0x08, 0x07, 0xF0, 0x00,
0x00, 0x00, 

/* character 0x0046 ('F'): (width = 8, offset = 278) */
0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,


/* character 0x0047 ('G'): (width = 10, offset = 294) */
0x00, 0x00, 0x00, 0x00, 0x78, 0x21, 0x10, 0x24, 0x01, 0x00, 0x47, 0x90, 0x24, 0x08, 0x84, 0x1E,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0048 ('H'): (width = 9, offset = 314) */
0x00, 0x00, 0x00, 0x08, 0x24, 0x12, 0x09, 0x04, 0xFE, 0x41, 0x20, 0x90, 0x48, 0x24, 0x10, 0x00,
0x00, 0x00, 

/* character 0x0049 ('I'): (width = 3, offset = 332) */
0x00, 0x24, 0x92, 0x49, 0x24, 0x00, 

/* character 0x004A ('J'): (width = 6, offset = 338) */
0x00, 0x00, 0x02, 0x08, 0x20, 0x82, 0x08, 0x28, 0xA2, 0x70, 0x00, 0x00, 

/* character 0x004B ('K'): (width = 9, offset = 350) */
0x00, 0x00, 0x00, 0x08, 0x14, 0x12, 0x11, 0x10, 0x90, 0x58, 0x32, 0x10, 0x88, 0x24, 0x08, 0x00,
0x00, 0x00, 

/* character 0x004C ('L'): (width = 7, offset = 368) */
0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x02, 0x07, 0xE0, 0x00, 0x00, 

/* character 0x004D ('M'): (width = 11, offset = 382) */
0x00, 0x00, 0x00, 0x00, 0x20, 0x26, 0x0C, 0xC1, 0x94, 0x52, 0x8A, 0x4A, 0x49, 0x49, 0x29, 0x22,
0x24, 0x44, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004E ('N'): (width = 9, offset = 404) */
0x00, 0x00, 0x00, 0x08, 0x26, 0x12, 0x89, 0x44, 0x92, 0x49, 0x22, 0x91, 0x48, 0x64, 0x10, 0x00,
0x00, 0x00, 

/* character 0x004F ('O'): (width = 10, offset = 422) */
0x00, 0x00, 0x00, 0x00, 0x78, 0x21, 0x10, 0x24, 0x09, 0x02, 0x40, 0x90, 0x24, 0x08, 0x84, 0x1E,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0050 ('P'): (width = 9, offset = 442) */
0x00, 0x00, 0x00, 0x0F, 0xC4, 0x12, 0x09, 0x04, 0x82, 0x7E, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00,
0x00, 0x00, 

/* character 0x0051 ('Q'): (width = 10, offset = 460) */
0x00, 0x00, 0x00, 0x00, 0x78, 0x21, 0x10, 0x24, 0x09, 0x02, 0x40, 0x90, 0x24, 0x68, 0x84, 0x1E,
0x80, 0x00, 0x00, 0x00, 

/* character 0x0052 ('R'): (width = 9, offset = 480) */
0x00, 0x00, 0x00, 0x0F, 0xC4, 0x12, 0x09, 0x04, 0x82, 0x7E, 0x22, 0x10, 0x88, 0x44, 0x10, 0x00,
0x00, 0x00, 

/* character 0x0053 ('S'): (width = 9, offset = 498) */
0x00, 0x00, 0x00, 0x07, 0xC4, 0x12, 0x09, 0x00, 0x70, 0x06, 0x00, 0x90, 0x48, 0x23, 0xE0, 0x00,
0x00, 0x00, 

/* character 0x0054 ('T'): (width = 7, offset = 516) */
0x00, 0x00, 0x07, 0xF1, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x00, 0x00, 0x00, 

/* character 0x0055 ('U'): (width = 9, offset = 530) */
0x00, 0x00, 0x00, 0x08, 0x24, 0x12, 0x09, 0x04, 0x82, 0x41, 0x20, 0x90, 0x44, 0x41, 0xC0, 0x00,
0x00, 0x00, 

/* character 0x0056 ('V'): (width = 9, offset = 548) */
0x00, 0x00, 0x00, 0x10, 0x18, 0x0A, 0x09, 0x04, 0x44, 0x22, 0x0A, 0x05, 0x01, 0x00, 0x80, 0x00,
0x00, 0x00, 

/* character 0x0057 ('W'): (width = 13, offset = 566) */
0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x18, 0x50, 0xA2, 0x89, 0x14, 0x48, 0xA2, 0x28, 0xA1, 0x45,
0x0A, 0x28, 0x20, 0x81, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0058 ('X'): (width = 7, offset = 592) */
0x00, 0x00, 0x04, 0x14, 0x48, 0x8A, 0x08, 0x10, 0x51, 0x12, 0x28, 0x20, 0x00, 0x00, 

/* character 0x0059 ('Y'): (width = 9, offset = 606) */
0x00, 0x00, 0x00, 0x08, 0x22, 0x21, 0x10, 0x50, 0x28, 0x08, 0x04, 0x02, 0x01, 0x00, 0x80, 0x00,
0x00, 0x00, 

/* character 0x005A ('Z'): (width = 7, offset = 624) */
0x00, 0x00, 0x03, 0xF0, 0x41, 0x02, 0x08, 0x10, 0x40, 0x82, 0x0F, 0xE0, 0x00, 0x00, 

/* character 0x0061 ('a'): (width = 7, offset = 638) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x22, 0x04, 0x79, 0x12, 0x63, 0x40, 0x00, 0x00, 

/* character 0x0062 ('b'): (width = 7, offset = 652) */
0x00, 0x00, 0x02, 0x04, 0x08, 0x16, 0x32, 0x44, 0x89, 0x12, 0x27, 0x80, 0x00, 0x00, 

/* character 0x0063 ('c'): (width = 7, offset = 666) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x22, 0x40, 0x81, 0x02, 0x23, 0x80, 0x00, 0x00, 

/* character 0x0064 ('d'): (width = 7, offset = 680) */
0x00, 0x00, 0x00, 0x20, 0x40, 0x8D, 0x26, 0x44, 0x89, 0x12, 0x23, 0xC0, 0x00, 0x00, 

/* character 0x0065 ('e'): (width = 7, offset = 694) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x22, 0x44, 0xF9, 0x02, 0x23, 0x80, 0x00, 0x00, 

/* character 0x0066 ('f'): (width = 3, offset = 708) */
0x00, 0x14, 0xBA, 0x49, 0x24, 0x00, 

/* character 0x0067 ('g'): (width = 7, offset = 714) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x26, 0x44, 0x89, 0x12, 0x63, 0x40, 0x91, 0x1C, 

/* character 0x0068 ('h'): (width = 7, offset = 728) */
0x00, 0x00, 0x02, 0x04, 0x08, 0x16, 0x32, 0x44, 0x89, 0x12, 0x24, 0x40, 0x00, 0x00, 

/* character 0x0069 ('i'): (width = 3, offset = 742) */
0x00, 0x20, 0x12, 0x49, 0x24, 0x00, 

/* character 0x006A ('j'): (width = 3, offset = 748) */
0x00, 0x20, 0x12, 0x49, 0x24, 0x94, 

/* character 0x006B ('k'): (width = 7, offset = 754) */
0x00, 0x00, 0x02, 0x04, 0x08, 0x11, 0x24, 0x50, 0xE1, 0x22, 0x44, 0x40, 0x00, 0x00, 

/* character 0x006C ('l'): (width = 3, offset = 768) */
0x00, 0x24, 0x92, 0x49, 0x24, 0x00, 

/* character 0x006D ('m'): (width = 11, offset = 774) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x63, 0x32, 0x44, 0x48, 0x89, 0x11, 0x22,
0x24, 0x44, 0x00, 0x00, 0x00, 0x00, 

/* character 0x006E ('n'): (width = 7, offset = 796) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x32, 0x44, 0x89, 0x12, 0x24, 0x40, 0x00, 0x00, 

/* character 0x006F ('o'): (width = 7, offset = 810) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x22, 0x44, 0x89, 0x12, 0x23, 0x80, 0x00, 0x00, 

/* character 0x0070 ('p'): (width = 7, offset = 824) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x32, 0x44, 0x89, 0x13, 0x25, 0x88, 0x10, 0x20, 

/* character 0x0071 ('q'): (width = 7, offset = 838) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x26, 0x44, 0x89, 0x12, 0x63, 0x40, 0x81, 0x02, 

/* character 0x0072 ('r'): (width = 4, offset = 852) */
0x00, 0x00, 0x00, 0x56, 0x44, 0x44, 0x40, 0x00, 

/* character 0x0073 ('s'): (width = 7, offset = 860) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x22, 0x40, 0x70, 0x12, 0x23, 0x80, 0x00, 0x00, 

/* character 0x0074 ('t'): (width = 4, offset = 874) */
0x00, 0x00, 0x44, 0xE4, 0x44, 0x44, 0x60, 0x00, 

/* character 0x0075 ('u'): (width = 7, offset = 882) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x44, 0x89, 0x12, 0x23, 0xC0, 0x00, 0x00, 

/* character 0x0076 ('v'): (width = 5, offset = 896) */
0x00, 0x00, 0x00, 0x02, 0x31, 0x52, 0x94, 0x42, 0x00, 0x00, 

/* character 0x0077 ('w'): (width = 9, offset = 906) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x23, 0x11, 0x55, 0x2A, 0x95, 0x44, 0x42, 0x20, 0x00,
0x00, 0x00, 

/* character 0x0078 ('x'): (width = 7, offset = 924) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x14, 0x28, 0x20, 0xA1, 0x44, 0x40, 0x00, 0x00, 

/* character 0x0079 ('y'): (width = 7, offset = 938) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x28, 0x50, 0xA0, 0x81, 0x02, 0x04, 0x30, 

/* character 0x007A ('z'): (width = 7, offset = 952) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x04, 0x08, 0x20, 0x81, 0x07, 0xC0, 0x00, 0x00

};

const D4D_FONT_OFFSET d4dfnt_Arial_10_offset_table[] = { 

/*       offset       char      hexcode     */
/*       ======      =====      =======     */
            0,    /*   ' '        0020       */
            8,    /*   '+'        002B       */
           24,    /*   '-'        002D       */
           32,    /*   '.'        002E       */
           40,    /*   '0'        0030       */
           54,    /*   '1'        0031       */
           68,    /*   '2'        0032       */
           82,    /*   '3'        0033       */
           96,    /*   '4'        0034       */
          110,    /*   '5'        0035       */
          124,    /*   '6'        0036       */
          138,    /*   '7'        0037       */
          152,    /*   '8'        0038       */
          166,    /*   '9'        0039       */
          180,    /*   ':'        003A       */
          188,    /*   'A'        0041       */
          206,    /*   'B'        0042       */
          224,    /*   'C'        0043       */
          242,    /*   'D'        0044       */
          260,    /*   'E'        0045       */
          278,    /*   'F'        0046       */
          294,    /*   'G'        0047       */
          314,    /*   'H'        0048       */
          332,    /*   'I'        0049       */
          338,    /*   'J'        004A       */
          350,    /*   'K'        004B       */
          368,    /*   'L'        004C       */
          382,    /*   'M'        004D       */
          404,    /*   'N'        004E       */
          422,    /*   'O'        004F       */
          442,    /*   'P'        0050       */
          460,    /*   'Q'        0051       */
          480,    /*   'R'        0052       */
          498,    /*   'S'        0053       */
          516,    /*   'T'        0054       */
          530,    /*   'U'        0055       */
          548,    /*   'V'        0056       */
          566,    /*   'W'        0057       */
          592,    /*   'X'        0058       */
          606,    /*   'Y'        0059       */
          624,    /*   'Z'        005A       */
          638,    /*   'a'        0061       */
          652,    /*   'b'        0062       */
          666,    /*   'c'        0063       */
          680,    /*   'd'        0064       */
          694,    /*   'e'        0065       */
          708,    /*   'f'        0066       */
          714,    /*   'g'        0067       */
          728,    /*   'h'        0068       */
          742,    /*   'i'        0069       */
          748,    /*   'j'        006A       */
          754,    /*   'k'        006B       */
          768,    /*   'l'        006C       */
          774,    /*   'm'        006D       */
          796,    /*   'n'        006E       */
          810,    /*   'o'        006F       */
          824,    /*   'p'        0070       */
          838,    /*   'q'        0071       */
          852,    /*   'r'        0072       */
          860,    /*   's'        0073       */
          874,    /*   't'        0074       */
          882,    /*   'u'        0075       */
          896,    /*   'v'        0076       */
          906,    /*   'w'        0077       */
          924,    /*   'x'        0078       */
          938,    /*   'y'        0079       */
          952    /*   'z'        007A       */
};

const D4D_FONT_IX d4dfnt_Arial_10_index_table[] = { 

/*        char      hexacode      decimal       index     */
/*       ======     ========      =======      =======    */
          ' ',    /*   0020          32            0       */
          '+',    /*   002B          43            1       */
          '-',    /*   002D          45            2       */
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

const D4D_FONT_SIZE d4dfnt_Arial_10_width_table[] = { 

/*       width        char      hexcode     */
/*       ======      =====      =======     */
           4,    /*   ' '        0020       */
           8,    /*   '+'        002B       */
           4,    /*   '-'        002D       */
           4,    /*   '.'        002E       */
           7,    /*   '0'        0030       */
           7,    /*   '1'        0031       */
           7,    /*   '2'        0032       */
           7,    /*   '3'        0033       */
           7,    /*   '4'        0034       */
           7,    /*   '5'        0035       */
           7,    /*   '6'        0036       */
           7,    /*   '7'        0037       */
           7,    /*   '8'        0038       */
           7,    /*   '9'        0039       */
           4,    /*   ':'        003A       */
           9,    /*   'A'        0041       */
           9,    /*   'B'        0042       */
           9,    /*   'C'        0043       */
           9,    /*   'D'        0044       */
           9,    /*   'E'        0045       */
           8,    /*   'F'        0046       */
          10,    /*   'G'        0047       */
           9,    /*   'H'        0048       */
           3,    /*   'I'        0049       */
           6,    /*   'J'        004A       */
           9,    /*   'K'        004B       */
           7,    /*   'L'        004C       */
          11,    /*   'M'        004D       */
           9,    /*   'N'        004E       */
          10,    /*   'O'        004F       */
           9,    /*   'P'        0050       */
          10,    /*   'Q'        0051       */
           9,    /*   'R'        0052       */
           9,    /*   'S'        0053       */
           7,    /*   'T'        0054       */
           9,    /*   'U'        0055       */
           9,    /*   'V'        0056       */
          13,    /*   'W'        0057       */
           7,    /*   'X'        0058       */
           9,    /*   'Y'        0059       */
           7,    /*   'Z'        005A       */
           7,    /*   'a'        0061       */
           7,    /*   'b'        0062       */
           7,    /*   'c'        0063       */
           7,    /*   'd'        0064       */
           7,    /*   'e'        0065       */
           3,    /*   'f'        0066       */
           7,    /*   'g'        0067       */
           7,    /*   'h'        0068       */
           3,    /*   'i'        0069       */
           3,    /*   'j'        006A       */
           7,    /*   'k'        006B       */
           3,    /*   'l'        006C       */
          11,    /*   'm'        006D       */
           7,    /*   'n'        006E       */
           7,    /*   'o'        006F       */
           7,    /*   'p'        0070       */
           7,    /*   'q'        0071       */
           4,    /*   'r'        0072       */
           7,    /*   's'        0073       */
           4,    /*   't'        0074       */
           7,    /*   'u'        0075       */
           5,    /*   'v'        0076       */
           9,    /*   'w'        0077       */
           7,    /*   'x'        0078       */
           7,    /*   'y'        0079       */
           7     /*   'z'        007A       */
};

const D4D_FONT_DESCRIPTOR d4dfnt_Arial_10_desc = {
    0,       // Font descriptor version number
    D4D_FONT_FLAGS_IX_STYLE_NONLINEAR | D4D_FONT_FLAGS_IX_TYPE_MAP | D4D_FONT_FLAGS_FNT_WIDTH_PROPORTIONAL,   // linear / nonlinear , proporcional or not
    ' ',     // start char of used table
    67,   // count of all chars of used table
    0x0020,     // index of char that will be printed instead of
    10,       // font size (size of font loaded in PC)
    0,     // height of font bitmpap for non proporcional fonts
    13,      // offset from Y0 coordination to baseline
    {13, 16},     // size of biggest char x/y
    D4D_FONT_PACK_BITORDER_BIGEND | D4D_FONT_PACK_SCANBASED_ROW | D4D_FONT_PACK_SCANPREFERRED_ROW | D4D_FONT_PACK_COMPRESSED_ON,     // packing condition of individual bitmaps
    d4dfnt_Arial_10_index_table,          // Index table - is used when nonlinearIX is set in flags, flags also determine the type of IxTable
    d4dfnt_Arial_10_offset_table,     // Offset table - used when proporcial font is set in flags
    d4dfnt_Arial_10_width_table,        // Size table - used when proporcial font is set in flags
    d4dfnt_Arial_10_data_table,      // bitmap/font data array
    NULL       // pointer for next UNICODE page
};

const Byte d4dfnt_Arial_11_data_table[] = { 

/* character 0x0020 (' '): (width = 4, offset = 0) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x002B ('+'): (width = 9, offset = 9) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x7F, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 

/* character 0x002D ('-'): (width = 5, offset = 29) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 

/* character 0x002E ('.'): (width = 4, offset = 40) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 

/* character 0x0030 ('0'): (width = 8, offset = 49) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0031 ('1'): (width = 8, offset = 66) */
0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
0x00, 

/* character 0x0032 ('2'): (width = 8, offset = 83) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 0x02, 0x04, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00, 0x00,
0x00, 

/* character 0x0033 ('3'): (width = 8, offset = 100) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 0x02, 0x1C, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0034 ('4'): (width = 8, offset = 117) */
0x00, 0x00, 0x00, 0x04, 0x0C, 0x14, 0x24, 0x24, 0x44, 0x84, 0xFE, 0x04, 0x04, 0x04, 0x00, 0x00,
0x00, 

/* character 0x0035 ('5'): (width = 8, offset = 134) */
0x00, 0x00, 0x00, 0x3E, 0x20, 0x20, 0x40, 0x7C, 0x42, 0x02, 0x02, 0x42, 0x44, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0036 ('6'): (width = 8, offset = 151) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0037 ('7'): (width = 8, offset = 168) */
0x00, 0x00, 0x00, 0x7E, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
0x00, 

/* character 0x0038 ('8'): (width = 8, offset = 185) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0039 ('9'): (width = 8, offset = 202) */
0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x003A (':'): (width = 4, offset = 219) */
0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x00, 

/* character 0x0041 ('A'): (width = 9, offset = 228) */
0x00, 0x00, 0x00, 0x01, 0x01, 0x40, 0xA0, 0x50, 0x44, 0x22, 0x20, 0x9F, 0xC8, 0x28, 0x0C, 0x04,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0042 ('B'): (width = 10, offset = 248) */
0x00, 0x00, 0x00, 0x01, 0xFC, 0x40, 0x90, 0x24, 0x09, 0x04, 0x7F, 0x10, 0x24, 0x09, 0x02, 0x40,
0x9F, 0xC0, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0043 ('C'): (width = 11, offset = 270) */
0x00, 0x00, 0x00, 0x00, 0x07, 0x83, 0x08, 0x40, 0x90, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x10,
0x23, 0x08, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0044 ('D'): (width = 11, offset = 294) */
0x00, 0x00, 0x00, 0x00, 0x3F, 0x84, 0x08, 0x80, 0x90, 0x12, 0x02, 0x40, 0x48, 0x09, 0x01, 0x20,
0x24, 0x08, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0045 ('E'): (width = 10, offset = 318) */
0x00, 0x00, 0x00, 0x01, 0xFE, 0x40, 0x10, 0x04, 0x01, 0x00, 0x7F, 0x90, 0x04, 0x01, 0x00, 0x40,
0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0046 ('F'): (width = 9, offset = 340) */
0x00, 0x00, 0x00, 0x0F, 0xE4, 0x02, 0x01, 0x00, 0x80, 0x7E, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0047 ('G'): (width = 11, offset = 360) */
0x00, 0x00, 0x00, 0x00, 0x0F, 0x82, 0x08, 0x80, 0x90, 0x02, 0x00, 0x43, 0xC8, 0x09, 0x01, 0x20,
0x22, 0x08, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0048 ('H'): (width = 10, offset = 384) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x90, 0x24, 0x09, 0x02, 0x7F, 0x90, 0x24, 0x09, 0x02, 0x40,
0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0049 ('I'): (width = 3, offset = 406) */
0x00, 0x24, 0x92, 0x49, 0x24, 0x80, 0x00, 

/* character 0x004A ('J'): (width = 7, offset = 413) */
0x00, 0x00, 0x00, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x14, 0x28, 0x4F, 0x00, 0x00, 0x00, 

/* character 0x004B ('K'): (width = 10, offset = 428) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x41, 0x10, 0x84, 0x41, 0x20, 0x54, 0x18, 0x84, 0x21, 0x04, 0x40,
0x90, 0x10, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004C ('L'): (width = 8, offset = 450) */
0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x00, 0x00,
0x00, 

/* character 0x004D ('M'): (width = 11, offset = 467) */
0x00, 0x00, 0x00, 0x00, 0x20, 0x26, 0x0C, 0xC1, 0x94, 0x52, 0x8A, 0x51, 0x49, 0x49, 0x29, 0x25,
0x24, 0x44, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004E ('N'): (width = 10, offset = 491) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x60, 0x94, 0x25, 0x09, 0x22, 0x48, 0x91, 0x24, 0x29, 0x0A, 0x41,
0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 

/* character 0x004F ('O'): (width = 12, offset = 513) */
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x30, 0xC2, 0x04, 0x40, 0x24, 0x02, 0x40, 0x24, 0x02, 0x40,
0x22, 0x04, 0x30, 0xC0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0050 ('P'): (width = 10, offset = 539) */
0x00, 0x00, 0x00, 0x01, 0xFC, 0x40, 0x90, 0x24, 0x09, 0x02, 0x7F, 0x10, 0x04, 0x01, 0x00, 0x40,
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0051 ('Q'): (width = 12, offset = 561) */
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x30, 0xC2, 0x04, 0x40, 0x24, 0x02, 0x40, 0x24, 0x02, 0x40,
0x22, 0x34, 0x30, 0xC0, 0xF2, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0052 ('R'): (width = 11, offset = 587) */
0x00, 0x00, 0x00, 0x00, 0x3F, 0xC4, 0x04, 0x80, 0x90, 0x12, 0x02, 0x7F, 0x88, 0x41, 0x04, 0x20,
0x84, 0x08, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0053 ('S'): (width = 10, offset = 611) */
0x00, 0x00, 0x00, 0x00, 0x78, 0x21, 0x10, 0x24, 0x01, 0xE0, 0x07, 0x00, 0x20, 0x09, 0x02, 0x61,
0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0054 ('T'): (width = 9, offset = 633) */
0x00, 0x00, 0x00, 0x1F, 0xF0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x80, 0x40,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0055 ('U'): (width = 10, offset = 653) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x40, 0x90, 0x24, 0x09, 0x02, 0x40, 0x90, 0x24, 0x09, 0x02, 0x21,
0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0056 ('V'): (width = 9, offset = 675) */
0x00, 0x00, 0x00, 0x10, 0x18, 0x0A, 0x09, 0x04, 0x44, 0x22, 0x11, 0x05, 0x02, 0x80, 0x80, 0x40,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0057 ('W'): (width = 15, offset = 695) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x18, 0x28, 0x28, 0x50, 0x90, 0xA1, 0x22, 0x22, 0x44,
0x44, 0x48, 0x90, 0xA0, 0xA1, 0x41, 0x41, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,


/* character 0x0058 ('X'): (width = 9, offset = 727) */
0x00, 0x00, 0x00, 0x10, 0x14, 0x11, 0x10, 0x88, 0x28, 0x08, 0x0A, 0x08, 0x84, 0x44, 0x14, 0x04,
0x00, 0x00, 0x00, 0x00, 

/* character 0x0059 ('Y'): (width = 9, offset = 747) */
0x00, 0x00, 0x00, 0x10, 0x14, 0x11, 0x10, 0x88, 0x28, 0x08, 0x04, 0x02, 0x01, 0x00, 0x80, 0x40,
0x00, 0x00, 0x00, 0x00, 

/* character 0x005A ('Z'): (width = 8, offset = 767) */
0x00, 0x00, 0x00, 0x7F, 0x02, 0x04, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0xFF, 0x00, 0x00,
0x00, 

/* character 0x0061 ('a'): (width = 8, offset = 784) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x02, 0x1E, 0x22, 0x42, 0x46, 0x3A, 0x00, 0x00,
0x00, 

/* character 0x0062 ('b'): (width = 8, offset = 801) */
0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x00, 0x00,
0x00, 

/* character 0x0063 ('c'): (width = 8, offset = 818) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0064 ('d'): (width = 8, offset = 835) */
0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00,
0x00, 

/* character 0x0065 ('e'): (width = 8, offset = 852) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0066 ('f'): (width = 4, offset = 869) */
0x00, 0x03, 0x44, 0xF4, 0x44, 0x44, 0x44, 0x00, 0x00, 

/* character 0x0067 ('g'): (width = 8, offset = 878) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x42,
0x3C, 

/* character 0x0068 ('h'): (width = 8, offset = 895) */
0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
0x00, 

/* character 0x0069 ('i'): (width = 3, offset = 912) */
0x00, 0x20, 0x12, 0x49, 0x24, 0x80, 0x00, 

/* character 0x006A ('j'): (width = 3, offset = 919) */
0x00, 0x20, 0x12, 0x49, 0x24, 0x92, 0x80, 

/* character 0x006B ('k'): (width = 7, offset = 926) */
0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0xA2, 0x48, 0xA1, 0xA2, 0x24, 0x48, 0x40, 0x00, 0x00, 

/* character 0x006C ('l'): (width = 3, offset = 941) */
0x00, 0x24, 0x92, 0x49, 0x24, 0x80, 0x00, 

/* character 0x006D ('m'): (width = 13, offset = 948) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x73, 0x8C, 0x62, 0x42, 0x12, 0x10,
0x90, 0x84, 0x84, 0x24, 0x21, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x006E ('n'): (width = 8, offset = 976) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
0x00, 

/* character 0x006F ('o'): (width = 8, offset = 993) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0070 ('p'): (width = 8, offset = 1010) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40,
0x40, 

/* character 0x0071 ('q'): (width = 8, offset = 1027) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x02,
0x02, 

/* character 0x0072 ('r'): (width = 5, offset = 1044) */
0x00, 0x00, 0x00, 0x01, 0x6C, 0x42, 0x10, 0x84, 0x20, 0x00, 0x00, 

/* character 0x0073 ('s'): (width = 8, offset = 1055) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x40, 0x30, 0x0C, 0x02, 0x42, 0x3C, 0x00, 0x00,
0x00, 

/* character 0x0074 ('t'): (width = 4, offset = 1072) */
0x00, 0x00, 0x44, 0xF4, 0x44, 0x44, 0x47, 0x00, 0x00, 

/* character 0x0075 ('u'): (width = 8, offset = 1081) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00,
0x00, 

/* character 0x0076 ('v'): (width = 7, offset = 1098) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xC1, 0x44, 0x88, 0xA1, 0x41, 0x02, 0x00, 0x00, 0x00, 

/* character 0x0077 ('w'): (width = 11, offset = 1113) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x0C, 0x51, 0x4A, 0x49, 0x49, 0x45, 0x28,
0xA2, 0x08, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0078 ('x'): (width = 7, offset = 1137) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xA2, 0x28, 0x20, 0x41, 0x44, 0x50, 0x40, 0x00, 0x00, 

/* character 0x0079 ('y'): (width = 7, offset = 1152) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xC1, 0x44, 0x88, 0xA1, 0x42, 0x82, 0x04, 0x08, 0x60, 

/* character 0x007A ('z'): (width = 8, offset = 1167) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x7E, 0x00, 0x00,
0x00

};

const D4D_FONT_OFFSET d4dfnt_Arial_11_offset_table[] = { 

/*       offset       char      hexcode     */
/*       ======      =====      =======     */
            0,    /*   ' '        0020       */
            9,    /*   '+'        002B       */
           29,    /*   '-'        002D       */
           40,    /*   '.'        002E       */
           49,    /*   '0'        0030       */
           66,    /*   '1'        0031       */
           83,    /*   '2'        0032       */
          100,    /*   '3'        0033       */
          117,    /*   '4'        0034       */
          134,    /*   '5'        0035       */
          151,    /*   '6'        0036       */
          168,    /*   '7'        0037       */
          185,    /*   '8'        0038       */
          202,    /*   '9'        0039       */
          219,    /*   ':'        003A       */
          228,    /*   'A'        0041       */
          248,    /*   'B'        0042       */
          270,    /*   'C'        0043       */
          294,    /*   'D'        0044       */
          318,    /*   'E'        0045       */
          340,    /*   'F'        0046       */
          360,    /*   'G'        0047       */
          384,    /*   'H'        0048       */
          406,    /*   'I'        0049       */
          413,    /*   'J'        004A       */
          428,    /*   'K'        004B       */
          450,    /*   'L'        004C       */
          467,    /*   'M'        004D       */
          491,    /*   'N'        004E       */
          513,    /*   'O'        004F       */
          539,    /*   'P'        0050       */
          561,    /*   'Q'        0051       */
          587,    /*   'R'        0052       */
          611,    /*   'S'        0053       */
          633,    /*   'T'        0054       */
          653,    /*   'U'        0055       */
          675,    /*   'V'        0056       */
          695,    /*   'W'        0057       */
          727,    /*   'X'        0058       */
          747,    /*   'Y'        0059       */
          767,    /*   'Z'        005A       */
          784,    /*   'a'        0061       */
          801,    /*   'b'        0062       */
          818,    /*   'c'        0063       */
          835,    /*   'd'        0064       */
          852,    /*   'e'        0065       */
          869,    /*   'f'        0066       */
          878,    /*   'g'        0067       */
          895,    /*   'h'        0068       */
          912,    /*   'i'        0069       */
          919,    /*   'j'        006A       */
          926,    /*   'k'        006B       */
          941,    /*   'l'        006C       */
          948,    /*   'm'        006D       */
          976,    /*   'n'        006E       */
          993,    /*   'o'        006F       */
         1010,    /*   'p'        0070       */
         1027,    /*   'q'        0071       */
         1044,    /*   'r'        0072       */
         1055,    /*   's'        0073       */
         1072,    /*   't'        0074       */
         1081,    /*   'u'        0075       */
         1098,    /*   'v'        0076       */
         1113,    /*   'w'        0077       */
         1137,    /*   'x'        0078       */
         1152,    /*   'y'        0079       */
         1167    /*   'z'        007A       */
};

const D4D_FONT_IX d4dfnt_Arial_11_index_table[] = { 

/*        char      hexacode      decimal       index     */
/*       ======     ========      =======      =======    */
          ' ',    /*   0020          32            0       */
          '+',    /*   002B          43            1       */
          '-',    /*   002D          45            2       */
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
           9,    /*   '+'        002B       */
           5,    /*   '-'        002D       */
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

