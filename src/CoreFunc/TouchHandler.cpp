#include "./CoreFunc/TouchHandler.h"

int TouchHandler::typeEvent = 0;
uint16_t TouchHandler::x = 0;
uint16_t TouchHandler::y = 0;
TS_Point TouchHandler::last = TS_Point();
bool TouchHandler::draw = false;
bool TouchHandler::pressed = false;
TFT_eSPI* TouchHandler::tft = NULL;

TouchHandler::TouchHandler(TFT_eSPI *t)
{
    tft = t;
    x = 0;
    y = 0;
    ts = new XPT2046_Touchscreen(CS_PIN,TIRQ_PIN);
    ts->begin();
    ts->setRotation(5);
    tevent = new TouchEvent(*ts);
    tevent->setResolution(240,320);
    tevent->setDblClick(200);
    tevent->registerOnTouchClick(onClick);
    tevent->registerOnTouchDblClick(onDblClick);
    tevent->registerOnTouchLong(onLongClick);
    tevent->registerOnTouchSwipe(onSwipe);
    tevent->registerOnTouchDown(onTouch);
    tevent->registerOnTouchUp(onUnTouch);
    tevent->setDrawMode(false);
}
void TouchHandler::touchtask()
{
  uint16_t t_x = 0, t_y = 0;
  pressed = tft->getTouch(&t_x,&t_y);
  x = t_x;
  y = t_y;
  // if(pressed)
  //   Serial.printf("X = %d, Y = %d \n",x,y);
}

void TouchHandler::onSwipe(uint8_t dir){
  switch (dir){
    case 0:
      TouchHandler::typeEvent = 4;
      Serial.println("Swipe left");
      // pressed = tft->getTouch(&x,&y);
      // Serial.printf("X = %d, Y = %d \n",x,y);
      break;
      
    case 1:
      TouchHandler::typeEvent = -4;
      Serial.println("Swipe right");
      // pressed = tft->getTouch(&x,&y);
      // Serial.printf("X = %d, Y = %d \n",x,y);
      break;
    case 2:
      TouchHandler::typeEvent = 5;
      Serial.println("Swipe up");
      // pressed = tft->getTouch(&x,&y);
      // Serial.printf("X = %d, Y = %d \n",x,y);
      break;
    case 3:
      TouchHandler::typeEvent = -5;
      Serial.println("Swipe down");
      // pressed = tft->getTouch(&x,&y);
      // Serial.printf("X = %d, Y = %d \n",x,y);
      break;
}
  
}

void TouchHandler::onClick(TS_Point p)
{
  TouchHandler::typeEvent = 1;
  Serial.println("Touch");
}

void TouchHandler::onDblClick(TS_Point p)
{
  TouchHandler::typeEvent = 2;
  Serial.println("Double Touch");
}

void TouchHandler::onLongClick(TS_Point p)
{
  TouchHandler::typeEvent = 3;
  Serial.println("Long Press");
}

void TouchHandler::onTouch(TS_Point p)
{
  x = p.x;
  y = p.y;
  //Serial.printf("X = %d, Y = %d \n",p.x,p.y);
}


void TouchHandler::onUnTouch(TS_Point p)
{
  TouchHandler::typeEvent = 0;
  x = p.x;
  y = p.y;
  //Serial.printf("X = %d, Y = %d \n",p.x,p.y);
}