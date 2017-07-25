#ifndef _NEST_H_
#define _NEST_H_

#include <Arduino.h>


class Nest
{
  private:
    uint8_t nestID;
    float temperature;
    float humidity;
    int   xDeg;
    int   yDeg;
    int   zDeg;


  public:
    Nest();
    Nest(uint8_t nestID);
    Nest(uint8_t nestID, float temp, float hum, int xDeg, int yDeg, int zDeg);
    
    uint8_t GetNestID()       {return nestID;}
    float   GetTemperature()  {return temperature;}
    float   GetHumidity()     {return humidity;}
    int     GetXDegrees()     {return xDeg;}
    int     GetYDegrees()     {return yDeg;}
    int     GetZDegrees()     {return zDeg;}
    char*   ToString(Nest n);
};

#endif // _NEST_H_
