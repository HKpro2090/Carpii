#include "./Apps/Homeapp.h"



void Homeapp::homescreen()
{
    hil.icon1[0] = 49;
    hil.icon1[1] = 54;
    hil.icon2[0] = 136;
    hil.icon2[1] = 54;
    hil.icon3[0] = 50;
    hil.icon3[1] = 138;
    hil.icon4[0] = 136;
    hil.icon4[1] = 138;

    hil.icon1dot[0] = 74;
    hil.icon1dot[1] = 107;

    hil.icon2dot[0] = 159;
    hil.icon2dot[1] = 107;
    
    hil.icon3dot[0] = 74;
    hil.icon3dot[1] = 190;

    hil.icon4dot[0] = 162;
    hil.icon4dot[1] = 190;

    appservices.tmsp->timeupdate();
    

    if((strcmp(ptimedate,appservices.tmsp->timedate)) || (strcmp(ptimemonth,appservices.tmsp->timemonth)) || (strcmp(ptimeday,appservices.tmsp->timeday)))
    {
        appservices.display->drawCircle(120,120,120,TFT_WHITE);
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
        appservices.display->drawCircle(120,120,120,TFT_WHITE);
        //TJpgDec.setJpgScale(1);
        prevtime = millis();
        prevcounter = -1;
        screenpagecounter = 1;
    }
    if(screenpagecounter == 1)
    {
        TJpgDec.drawSdJpg(hil.icon1[0], hil.icon1[1], "/AppIcons/Weather.jpg");
        TJpgDec.drawSdJpg(hil.icon2[0], hil.icon2[1], "/AppIcons/Alarmclock.jpg");
        TJpgDec.drawSdJpg(hil.icon3[0], hil.icon3[1], "/AppIcons/Walking.jpg");
        TJpgDec.drawSdJpg(hil.icon4[0], hil.icon4[1], "/AppIcons/Health.jpg");
        //TJpgDec.drawSdJpg(95, 211, "/AppIcons/Maps.jpg");
        //TJpgDec.drawSdJpg(169, 211, "/AppIcons/Settings.jpg");
        screenpagecounter = 2;
    }
    if(screenpagecounter == 2)
    {
        if(appservices.rotationinput->counter > 4)
        {
            appservices.rotationinput->counter = 1;
        }
        if(appservices.rotationinput->counter <= 0)
        {
            appservices.rotationinput->counter = 4;
        }
        if(prevcounter != appservices.rotationinput->counter)
        {
            if(appservices.rotationinput->counter == 1)
            {
                appservices.display->fillCircle(hil.icon1dot[0],hil.icon1dot[1],3,0x5a5aff);
                appservices.display->fillCircle(hil.icon2dot[0],hil.icon2dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon3dot[0],hil.icon3dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon4dot[0],hil.icon4dot[1],3,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 2)
            {
                appservices.display->fillCircle(hil.icon1dot[0],hil.icon1dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon2dot[0],hil.icon2dot[1],3,0x5a5aff);
                appservices.display->fillCircle(hil.icon3dot[0],hil.icon3dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon4dot[0],hil.icon4dot[1],3,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 3)
            {
                appservices.display->fillCircle(hil.icon1dot[0],hil.icon1dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon2dot[0],hil.icon2dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon3dot[0],hil.icon3dot[1],3,0x5a5aff);
                appservices.display->fillCircle(hil.icon4dot[0],hil.icon4dot[1],3,TFT_BLACK);
            }
            if(appservices.rotationinput->counter == 4)
            {
                appservices.display->fillCircle(hil.icon1dot[0],hil.icon1dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon2dot[0],hil.icon2dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon3dot[0],hil.icon3dot[1],3,TFT_BLACK);
                appservices.display->fillCircle(hil.icon4dot[0],hil.icon4dot[1],3,0x5a5aff);
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