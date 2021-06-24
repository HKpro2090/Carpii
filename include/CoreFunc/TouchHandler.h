#ifndef TOUCHHANDLE_H
#define TOUCHHANDLE_H
#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
#define TIRQ_PIN 39
#define CS_PIN 21 
class TouchHandler
{
private:
    XPT2046_Touchscreen *ts;
public:
    TouchHandler();
    int x,y;
    void touchtask();
};


#endif