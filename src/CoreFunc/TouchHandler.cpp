#include "./CoreFunc/TouchHandler.h"

TouchHandler::TouchHandler()
{
    x = 0;
    y = 0;
    ts = new XPT2046_Touchscreen(CS_PIN,TIRQ_PIN);
    ts->begin();
    ts->setRotation(0);
}
void TouchHandler::touchtask()
{
    if(ts->tirqTouched())
    {
      if(ts->touched())
      {
        TS_Point p = ts->getPoint();
        
        Serial.print("x = ");
        x = map(p.x,281,3848,0,240);
        y = map(p.y,347,3878,0,320);
        Serial.print(x);
        Serial.print(", y = ");
        Serial.println(y);
      }
    }
}