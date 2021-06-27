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
    int lastState = LOW;
    int currentState;
    unsigned long pressedTime  = 0;
    unsigned long releasedTime = 0;
    const int SHORT_PRESS_TIME = 500;
    const int LONG_PRESS_TIME  = 500;  
    public:
    int counter = 0;
    unsigned long lastButtonPress = 0;
    //bool buttonpress = false;
    bool shortpress = false;
    bool longpress = false;
    String currentDir = "";
    RotaryInput();
    void rotaryRotation();
    void rotarybutton();
};
#endif