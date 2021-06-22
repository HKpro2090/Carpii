#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
class Button
{
    public:
    int buttonid;
    static int buttoncount;
    String buttontext;
    Button(String text);
    void selected();
};
#endif