#include "./CoreFunc/Keyboard.h"

Keyboard::Keyboard(TFT_eSPI *t, TouchHandler *th)
{
    display = t;
    touch = th;
    keysprite = new TFT_eSprite(display);
    keysprite->setColorDepth(4);
    keysprite->setSwapBytes(true); 
    keysprite->createSprite(240,160);
    list = new LinkedList<String>();
    list->add("Hello World");
    list->add("Hello World 2");
    list->add("Hello World 3");
    list->add("Hello World 4");
    list->add("Hello World 5");
    list->add("Hello World 6");
    lv = new ListView(touch,t,list,20,20,150,200);
    lv->setPadding(15,20);

}
void Keyboard::keyboardtaskhandler()
{
    if(show == true)
    {
        if(screencounter == 0)
        {
            lv->loadView();  
            screencounter++;
        }
        if(screencounter == 1)
        {
            lv->show();
            screencounter++;
        }
        if(screencounter == 2)
        {
            lv->lvtouchtask();
        }
    }
}