/* Originating Author:
 *    Josh Kent 
 *    
 *  Contributing Authors:  
 *    <N/A>
 *  
 * Description:
 *    Class to store the temp array data and format data to a
 *    xBee compatible string. Data includes:
 *      +Temp 1
 *      +Temp 2
 *      +Temp 3
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


#ifndef _TEMPARRAY_H_
#define _TEMPARRAY_H_

#include <Arduino.h>

#define MAX_LINE  100

class TempArray
{
  private:
    uint8_t arrayNumber;
    int  bottom;
    int  middle;
    int  top;

    
  public:   
    TempArray(uint8_t ar);
    TempArray(int bottom, int middle, int top);
    
    int       GetBottomTemp()       {return bottom;}
    int       GetMiddleTemp()       {return middle;}
    int       GetTopTemp()          {return top;}
    void      SetBottomTemp(int b)  {bottom = b;} 
    void      SetMiddleTemp(int m)  {middle = m;}
    void      SetTopTemp(int t)     {top = t;}
    char*     ToString();
};

#endif // _TEMPARRAY_H_
