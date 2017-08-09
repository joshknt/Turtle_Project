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
