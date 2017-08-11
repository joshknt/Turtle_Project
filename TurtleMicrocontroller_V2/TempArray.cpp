/* Originating Author:
 *    Josh Kent 
 *    
 *  Contributing Authors:  
 *    <N/A>
 *  
 * Description:
 *    Implementation file for "TempArray.h"
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


#include "TempArray.h"

TempArray::TempArray(uint8_t ar)
{
  arrayNumber = ar;
  bottom  = -1;
  middle  = -1;
  top     = -1;
}

TempArray::TempArray(int bottom, int middle, int top)
{
  bottom  = bottom;
  middle  = middle;
  top     = top;
}

char* TempArray::ToString()
{
  char buffer[MAX_LINE];
  sprintf(buffer, "%d,%d,%d,%d\n", arrayNumber, bottom, middle, top);

  return buffer;
}

