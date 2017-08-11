/* Originating Author:
 *    Josh Kent 
 *    
 *  Contributing Authors:  
 *    <N/A>
 *  
 * Description:
 *    Implementation file for "Nest.h"
 * 
 * Notes:
 *    None.
 *    
 * 
 * License:
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    For a copy of the GNU General Public License, please visit
 *    <http://www.gnu.org/licenses/>.
 */

 
#include "Nest.h"
#include <Arduino.h>

Nest::Nest()
{
  nestID         = -1;
  temperature    = -1;
  humidity       = -1;
  xDeg           = -360;
  yDeg           = -360;
  zDeg           = -360;
}

Nest::Nest(uint8_t nestID)
{
  nestID = nestID;
}

Nest::Nest(uint8_t nestID, uint16_t temp, uint16_t hum, int16_t xDeg, int16_t yDeg, int16_t zDeg)
{
  nestID  = nestID;
  temp    = temperature;
  hum     = humidity;
  xDeg    = xDeg;
  yDeg    = yDeg;
  zDeg    = zDeg;
}

char* Nest::ToString()
{
  char buffer[MAX_LINE];
  sprintf(buffer, "%d,%d,%d,%d,%d,%d\n", nestID, temperature, humidity, xDeg, yDeg, zDeg);

  return buffer;
}

