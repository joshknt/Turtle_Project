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
