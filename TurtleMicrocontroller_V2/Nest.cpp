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

Nest::Nest(uint8_t nestID, float temp, float hum, int xDeg, int yDeg, int zDeg)
{
  nestID  = nestID;
  temp    = temperature;
  hum     = humidity;
  xDeg    = xDeg;
  yDeg    = yDeg;
  zDeg    = zDeg;
}

char* Nest::ToString(Nest n)
{
  char* buffer;

  sprintf(buffer, "%s", "dkfj");

  return buffer;
}

