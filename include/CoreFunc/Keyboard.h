#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <TFT_eSPI.h>
#include <CoreFunc/TouchHandler.h>
#include <GUIElements/ListView.h>
class Keyboard
{
    private:
    TFT_eSPI *display;
    TouchHandler *touch;
    TFT_eSprite *keysprite;
    TFT_eSPI_Button keybutton[26];
    int screencounter= 0;
    ListView *lv;
    LinkedList<String> *list;
    char keylabels[26] = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
    public:
    Keyboard(TFT_eSPI *t,TouchHandler *th);
    void keyboardtaskhandler();
    bool show = true;
};
#endif