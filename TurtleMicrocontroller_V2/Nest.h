#ifndef _NEST_H_
#define _NEST_H_

#include <Arduino.h>


class Nest
{
  private:
    float temperature;
    float humidity;
    int   xDeg;
    int   yDeg;
    int   zDeg;

  public:
  Nest();
  
};

#endif // _NEST_H_
