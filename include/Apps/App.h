#ifndef APP_H
#define APP_H
#include <Arduino.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/StartAppStruct.h>
#include <TJpg_Decoder.h>

class App
{
    public:
    bool pause = false;
    bool stopped = false;
    int appscreencounter = 0;
    int screenpagecounter = 0;
    String Appname = "";
    bool *stopapp;
    servicepointers appservices;
    StartAppStruct *newappstruct;
    App(struct servicepointers s, String apname,StartAppStruct *n,bool *stopappflag);
    String getappname();
};
#endif