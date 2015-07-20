/**
 ******************************************************************************
 * @file    brew_screen.h
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


#ifndef BREW_SCREEN_H
#define	BREW_SCREEN_H

#ifdef	__cplusplus
extern "C" {
#endif

    
D4D_EXTERN_SCREEN(screen_brew);

D4D_EXTERN_OBJECT(scrBrew_Name);

D4D_EXTERN_OBJECT(scrBrew_curHlt);
D4D_EXTERN_OBJECT(scrBrew_curMash);
D4D_EXTERN_OBJECT(scrBrew_curBoil);

D4D_EXTERN_OBJECT(scrBrew_tarHlt);
D4D_EXTERN_OBJECT(scrBrew_tarMash);
D4D_EXTERN_OBJECT(scrBrew_tarBoil);

D4D_EXTERN_OBJECT(scrBrew_togoHlt);
D4D_EXTERN_OBJECT(scrBrew_togoMash);
D4D_EXTERN_OBJECT(scrBrew_togoBoil);


#ifdef	__cplusplus
}
#endif

#endif	/* BREW_SCREEN_H */

