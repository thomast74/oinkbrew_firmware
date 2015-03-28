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

D4D_EXTERN_OBJECT(scrBrew_curHltIn);
D4D_EXTERN_OBJECT(scrBrew_curHltOut);
D4D_EXTERN_OBJECT(scrBrew_curMashIn);
D4D_EXTERN_OBJECT(scrBrew_curMashOut);
D4D_EXTERN_OBJECT(scrBrew_curBoilIn);
D4D_EXTERN_OBJECT(scrBrew_curBoilInside);
D4D_EXTERN_OBJECT(scrBrew_curBoilOut);

D4D_EXTERN_OBJECT(scrBrew_tarHltIn);
D4D_EXTERN_OBJECT(scrBrew_tarHltOut);
D4D_EXTERN_OBJECT(scrBrew_tarMashIn);
D4D_EXTERN_OBJECT(scrBrew_tarMashOut);
D4D_EXTERN_OBJECT(scrBrew_tarBoilIn);
D4D_EXTERN_OBJECT(scrBrew_tarBoilInside);
D4D_EXTERN_OBJECT(scrBrew_tarBoilOut);


#ifdef	__cplusplus
}
#endif

#endif	/* BREW_SCREEN_H */

