#include "./Apps/Homeapp.h"

Homeapp::Homeapp(struct servicepointers s)
{
    appservices.display = s.display;
    appservices.tmsp = s.tmsp;
}
void Homeapp::homescreen()
{
    appservices.tmsp->timeupdate();
    if((strcmp(ptimedate,appservices.tmsp->timedate)) || (strcmp(ptimemonth,appservices.tmsp->timemonth)) || (strcmp(ptimeday,appservices.tmsp->timeday)))
    {
        appservices.display->fillRect(25,66,120,30,TFT_BLACK);
        appservices.display->setCursor(28,70);
        appservices.display->loadFont("Roboto-Light-20",SD);
        appservices.display->setTextColor(TFT_BLACK);
        appservices.display->printf("%s, %s %s",appservices.tmsp->timeday,appservices.tmsp->timedate,appservices.tmsp->timemonth);
        appservices.display->setCursor(28,70);
        appservices.display->setTextColor(TFT_WHITE,TFT_BLACK);
        appservices.display->printf("%s, %s %s",appservices.tmsp->timeday,appservices.tmsp->timedate,appservices.tmsp->timemonth);
        appservices.display->unloadFont();
        strncpy(ptimeday,appservices.tmsp->timeday,4);
        strncpy(ptimemonth,appservices.tmsp->timemonth,4);
        strncpy(ptimedate,appservices.tmsp->timedate,3);
    }

    if(strcmp(ptimeHour,appservices.tmsp->timeHour))
    {
        //appservices.display->fillRect(51,96,70,52,TFT_BLACK);
        appservices.display->setCursor(55,113);
        appservices.display->loadFont("Roboto-Black-52",SD);
        appservices.display->setTextColor(TFT_BLACK);
        appservices.display->print(ptimeHour);
        appservices.display->setCursor(55,113);
        appservices.display->setTextColor(TFT_WHITE,TFT_BLACK);
        appservices.display->print(appservices.tmsp->timeHour);
        appservices.display->unloadFont();
        strncpy(ptimeHour,appservices.tmsp->timeHour,3);
    }

    if(strcmp(ptimeminute,appservices.tmsp->timeminute))
    {
        //appservices.display->fillRect(125,98,65,55,TFT_BLACK);
        appservices.display->setCursor(129,113);
        appservices.display->loadFont("Roboto-Light-52",SD);
        appservices.display->setTextColor(TFT_BLACK);
        appservices.display->print(ptimeminute);
        appservices.display->setCursor(129,113);
        appservices.display->setTextColor(TFT_WHITE,TFT_BLACK);
        appservices.display->print(appservices.tmsp->timeminute);
        appservices.display->unloadFont();
        strncpy(ptimeminute,appservices.tmsp->timeminute,3);
    }
    vTaskDelay(1000);
}
void Homeapp::homeapphandler()
{
    if(i == 0)
    {
        homescreen();
    }
    
}