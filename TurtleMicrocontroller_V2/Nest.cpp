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

