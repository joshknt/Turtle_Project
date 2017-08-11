/* Originating Author:
 *    Josh Kent 
 *    
 *  Contributing Authors:  
 *    <N/A>
 *  
 * Description:
 *    Class to store nest data and format data into a xBee compatible 
 *    string. Data includes:
 *      +NestID
 *      +Temperature
 *      +Humidity
 *      +Orientation
 *        -X
 *        -Y
 *        -Z
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


#ifndef _NEST_H_
#define _NEST_H_

#include <Arduino.h>

#define MAX_LINE  100

class Nest
{
  private:
    uint8_t   nestID;
    uint16_t   temperature;
    uint16_t   humidity;
    int16_t   xDeg;
    int16_t   yDeg;
    int16_t   zDeg;


  public:
    Nest();
    Nest(uint8_t nestID);
    Nest(uint8_t nestID, uint16_t temp, uint16_t hum, int16_t xDeg, int16_t yDeg, int16_t zDeg);
    
    uint8_t     GetNestID()       {return nestID;}
    uint16_t    GetTemperature()  {return temperature;}
    uint16_t    GetHumidity()     {return humidity;}
    int16_t     GetXDegrees()     {return xDeg;}
    int16_t     GetYDegrees()     {return yDeg;}
    int16_t     GetZDegrees()     {return zDeg;}
    int16_t     SetXDegrees(int16_t x)  {xDeg = x;}
    int16_t     SetYDegrees(int16_t y)  {yDeg = y;}
    int16_t     SetZDegrees(int16_t z)  {zDeg = z;}
    uint16_t    SetHumidity(uint16_t hum){humidity = hum;}
    uint16_t    SetTemperature(uint16_t temp) {temperature = temp;}
    char*       ToString();
};

#endif // _NEST_H_
