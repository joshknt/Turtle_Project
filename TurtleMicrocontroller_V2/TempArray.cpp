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

