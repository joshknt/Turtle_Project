#ifndef _NEST_H_
#define _NEST_H_

#include <Arduino.h>


class Nest
{
  private:
    uint8_t   nestID;
    int16_t   temperature;
    float     humidity;
    int16_t   xDeg;
    int16_t   yDeg;
    int16_t   zDeg;


  public:
    Nest();
    Nest(uint8_t nestID);
    Nest(uint8_t nestID, uint16_t temp, float hum, int16_t xDeg, int16_t yDeg, int16_t zDeg);
    
    uint8_t     GetNestID()       {return nestID;}
    uint16_t    GetTemperature()  {return temperature;}
    float       GetHumidity()     {return humidity;}
    int16_t     GetXDegrees()     {return xDeg;}
    int16_t     GetYDegrees()     {return yDeg;}
    int16_t     GetZDegrees()     {return zDeg;}
    char*       ToString();
};

#endif // _NEST_H_
