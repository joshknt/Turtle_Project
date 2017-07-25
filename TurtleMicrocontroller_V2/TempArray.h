#ifndef _TEMPARRAY_H_
#define _TEMPARRAY_H_

#include <Arduino.h>


class TempArray
{
  private:
    int  bottom;
    int  middle;
    int  top;

    
  public:
    TempArray();
    TempArray(int bottom, int middle, int top);
    
    int     GetBottomTemp()       {return bottom;}
    int     GetMiddleTemp()       {return middle;}
    int     GetTopTemp()          {return top;}
    void    SetBottomTemp(int b)  {bottom = b;} 
    void    SetMiddleTemp(int m)  {middle = m;}
    void    SetTopTemp(int t)     {top = t;}
    char*   ToString(TempArray a);
};

#endif // _TEMPARRAY_H_
