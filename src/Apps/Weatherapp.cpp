#include "./Apps/Weatherapp.h"

void Weatherapp::Weatherapphandler()
{
    Serial.println("Weather app");
    if(appservices.rotationinput->longpress)
    {
        appservices.rotationinput->longpress = false;
        appservices.display->fillScreen(TFT_BLACK);
        //newstopappstruct->stopapp = true;
        *stopapp = true;
    }

}
void Weatherapp::screen1()
{

}