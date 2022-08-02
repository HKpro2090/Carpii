#ifndef TOUCHHANDLE_H
#define TOUCHHANDLE_H
#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
#include <TouchEvent.h>
#include <TFT_eSPI.h>
#define TIRQ_PIN 39
#define CS_PIN 5 
class TouchHandler
{
private:
    XPT2046_Touchscreen *ts;
    static void onSwipe(uint8_t dir);
    static void onClick(TS_Point p);
    static void onDblClick(TS_Point p);
    static void onLongClick(TS_Point p);
    static void onDraw(TS_Point p);
    static void onTouch(TS_Point p);
    static void onUnTouch(TS_Point p);
    static TFT_eSPI *tft;
    
public:
    TouchHandler(TFT_eSPI *t);
    static uint16_t x,y;
    void touchtask();
    static int typeEvent;
    TouchEvent *tevent;
    static bool pressed;
    static TS_Point last;
    static bool draw;
    
};


#endif