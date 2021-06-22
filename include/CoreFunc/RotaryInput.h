#ifndef ROTARYINPUT_H
#define ROTARYINPUT_H
#include <Arduino.h>

#define ROTARY_ENCODER_CLK 34 //CLK (A pin)
#define ROTARY_ENCODER_DT 32 //DT (B pin)
#define ROTARY_ENCODER_SW 25


class RotaryInput
{
    private:
    int currentStateCLK;
    int lastStateCLK;
    public:
    int counter = 0;
    unsigned long lastButtonPress = 0;
    String currentDir = "";
    RotaryInput();
    void rotaryRotation();
    void rotarybutton();
};
#endif