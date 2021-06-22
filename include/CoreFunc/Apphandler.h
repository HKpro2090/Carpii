#ifndef APPHANDLER_H
#define APPHANDLER_H
#include <Arduino.h>
#include <CoreFunc/Timeservice.h>
#include <TFT_eSPI.h>
#include <CoreFunc/servicepointers.h>
#include <Apps/Homeapp.h>

class Apphandler
{
    private:
    TaskHandle_t Laucherapptask;
    struct servicepointers services;
    Homeapp *hap;
    public:
    bool otherapprunning;
    Apphandler(Timeservice* tmsp,TFT_eSPI *espi,RotaryInput *rip);
    void defaulttolauncher();
};
#endif