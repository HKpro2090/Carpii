#ifndef SERVICEPOINTERS_H
#define SERVICEPOINTERS_H
#include <CoreFunc/Timeservice.h>
#include <TFT_eSPI.h>
#include <CoreFunc/RotaryInput.h>
#include <SD.h>
#include <CoreFunc/TouchHandler.h>

struct servicepointers
{
    Timeservice *tmsp;
    TFT_eSPI *display;
    RotaryInput *rotationinput;
    TouchHandler *touchinput;
};

#endif