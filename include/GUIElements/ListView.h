#ifndef LISTVIEW_H
#define LISTVIEW_H
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <LinkedList.h>
#include <CoreFunc/TouchHandler.h>

class ListView
{
    private:
    int listitemno = 0;
    int posX = 0;
    int posY = 0;
    int width = 0;
    int height = 0;
    int paddingTop = 5;
    int paddingRight = 5;
    int paddingDown = 5;
    int paddingLeft = 5;
    int dividerWidth = 1;
    int cellheight = 0;
    int touchxsprite = 0;
    int touchysprite = 0;
    int pushspriteval = 0;
    int sprite_height = 0;
    float touch_zones = 0;
    int pusheditems = 0;
    TFT_eSPI *display;
    TFT_eSprite *sprite = NULL;
    LinkedList<String> *headlist = NULL;
    LinkedList<String> *subheadlist = NULL;
    TouchHandler *touch;
    public:
    ListView(TouchHandler *t,TFT_eSPI *d, LinkedList<String> *hlist,int x,int y,int w,int h);
    ListView(TouchHandler *t,TFT_eSPI *d, LinkedList<String> *hlist,LinkedList<String> *slist,int x,int y,int w,int h);
    void setPadding(int vertical,int horizontal);
    void setPadding(int padd);
    void setPadding(int t,int l, int r,int d);
    void setdividerwidth(int d);
    void loadView();
    void show();
    void lvtouchtask();
};
#endif