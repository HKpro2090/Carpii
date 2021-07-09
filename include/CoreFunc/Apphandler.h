#ifndef APPHANDLER_H
#define APPHANDLER_H
#include <Arduino.h>
#include <CoreFunc/Timeservice.h>
#include <TFT_eSPI.h>
#include <CoreFunc/servicepointers.h>
#include <Apps/Homeapp.h>
#include <CoreFunc/AppStackNode.h>
#include <CoreFunc/StartAppStruct.h>
#include <Apps/Weatherapp.h>
#include <TJpg_Decoder.h>

class Apphandler
{
    private:
    TaskHandle_t Laucherapptask;
    TaskHandle_t Weatherapptaskhandle;
    TaskHandle_t Alarmapptask;
    TaskHandle_t Workoutapptask;
    TaskHandle_t Healthapptask;
    TaskHandle_t Mapsapptask;
    TaskHandle_t settingsapptask;
    struct servicepointers services;
    struct AppStackNode *top = NULL;
    StartAppStruct startappstruct;
    bool stopapp = false;
    Homeapp *hap;
    Weatherapp *weap;
    public:
    Apphandler *aph;
    bool otherapprunning;
    Apphandler(Timeservice* tmsp,TFT_eSPI *espi,RotaryInput *rip,TouchHandler *th, Apphandler *selfaph);
    void appstackhandler();
    void updateservicepointer();
    void push(TaskHandle_t s);
    void startapp(char* s);
    void pop();
    void quitapp();
    void appflagchecker();
};
#endif