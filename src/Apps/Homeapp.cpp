#include "./Apps/Homeapp.h"

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
}
void Homeapp::homeapphandler()
{
    if(appscreencounter == 0)
    {
        homescreen();
        if(appservices.rotationinput->shortpress)
        {
            appscreencounter = 1;
            screenpagecounter = 0;
            appservices.rotationinput->shortpress = false;
        }
    }
    if(appscreencounter == 1)
    {
        menuscreen();
    }
    
}
void Homeapp::menuscreen()
{
    if(screenpagecounter == 0)
    {
        appservices.display->fillScreen(TFT_BLACK);
        //TJpgDec.setJpgScale(1);
        prevtime = millis();
        prevcounter = -1;
        screenpagecounter = 1;
    }
    if(screenpagecounter == 1)
    {
        TJpgDec.drawSdJpg(22, 48, "/AppIcons/Weather.jpg");
        TJpgDec.drawSdJpg(95, 48, "/AppIcons/Alarmclock.jpg");
        TJpgDec.drawSdJpg(169, 48, "/AppIcons/Walking.jpg");
        TJpgDec.drawSdJpg(22, 211, "/AppIcons/Health.jpg");
        TJpgDec.drawSdJpg(95, 211, "/AppIcons/Maps.jpg");
        TJpgDec.drawSdJpg(169, 211, "/AppIcons/Settings.jpg");
        screenpagecounter = 2;
    }
    if(screenpagecounter == 2)
    {
        if(appservices.rotationinput->counter > 6)
        {
            appservices.rotationinput->counter = 1;
        }
        if(appservices.rotationinput->counter <= 0)
        {
            appservices.rotationinput->counter = 6;
        }
        if(prevcounter != appservices.rotationinput->counter)
        {
            if(appservices.rotationinput->counter == 1)
            {
                appservices.display->fillCircle(47,109,2,0x5a5aff);
                appservices.display->fillCircle(120,109,2,TFT_BLACK);
                appservices.display->fillCircle(188,109,2,TFT_BLACK);
                appservices.display->fillCircle(47,268,2,TFT_BLACK);
                appservices.display->fillCircle(120,268,2,TFT_BLACK);
                appservices.display->fillCircle(190,268,2,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 2)
            {
                appservices.display->fillCircle(47,109,2,TFT_BLACK);
                appservices.display->fillCircle(120,109,2,0x5a5aff);
                appservices.display->fillCircle(188,109,2,TFT_BLACK);
                appservices.display->fillCircle(47,268,2,TFT_BLACK);
                appservices.display->fillCircle(120,268,2,TFT_BLACK);
                appservices.display->fillCircle(190,268,2,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 3)
            {
                appservices.display->fillCircle(47,109,2,TFT_BLACK);
                appservices.display->fillCircle(120,109,2,TFT_BLACK);
                appservices.display->fillCircle(188,109,2,0x5a5aff);
                appservices.display->fillCircle(47,268,2,TFT_BLACK);
                appservices.display->fillCircle(120,268,2,TFT_BLACK);
                appservices.display->fillCircle(190,268,2,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 4)
            {
                appservices.display->fillCircle(47,109,2,TFT_BLACK);
                appservices.display->fillCircle(120,109,2,TFT_BLACK);
                appservices.display->fillCircle(188,109,2,TFT_BLACK);
                appservices.display->fillCircle(47,268,2,0x5a5aff);
                appservices.display->fillCircle(120,268,2,TFT_BLACK);
                appservices.display->fillCircle(190,268,2,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 5)
            {
                appservices.display->fillCircle(47,109,2,TFT_BLACK);
                appservices.display->fillCircle(120,109,2,TFT_BLACK);
                appservices.display->fillCircle(188,109,2,TFT_BLACK);
                appservices.display->fillCircle(47,268,2,TFT_BLACK);
                appservices.display->fillCircle(120,268,2,0x5a5aff);
                appservices.display->fillCircle(190,268,2,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 6)
            {
                appservices.display->fillCircle(47,109,2,TFT_BLACK);
                appservices.display->fillCircle(120,109,2,TFT_BLACK);
                appservices.display->fillCircle(188,109,2,TFT_BLACK);
                appservices.display->fillCircle(47,268,2,TFT_BLACK);
                appservices.display->fillCircle(120,268,2,TFT_BLACK);
                appservices.display->fillCircle(190,268,2,0x5a5aff);
            }
            prevcounter = appservices.rotationinput->counter;
            prevtime = millis();
        }
        if(appservices.rotationinput->shortpress)
        {
            appservices.rotationinput->shortpress = false;
            if(appservices.rotationinput->counter == 1)
            {
                appservices.display->fillScreen(TFT_BLACK);
                screenpagecounter = 0;
                newappstruct->startingappname = "Weatherapp";
                newappstruct->startapp = true;
                //aph->startapp("Weatherapp");
                
            }
        }
        if(appservices.rotationinput->longpress)
        {
            appservices.rotationinput->longpress = false;
            appservices.display->fillScreen(TFT_BLACK);
            memset(ptimedate,0,sizeof(ptimedate));
            memset(ptimeHour,0,sizeof(ptimeHour));
            memset(ptimeminute,0,sizeof(ptimeminute));
            appscreencounter = 0;
        }
    }
}