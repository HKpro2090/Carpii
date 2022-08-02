#include "./GUIElements/ListView.h"

ListView::ListView(TouchHandler *t,TFT_eSPI *d,LinkedList<String> *hlist,int x,int y,int w,int h)
{
    touch = t;
    display = d;
    headlist = hlist;
    posX = x;
    posY = y;
    width = w;
    height = h;
    sprite = new TFT_eSprite(display);
}

ListView::ListView(TouchHandler *t,TFT_eSPI *d,LinkedList<String> *hlist,LinkedList<String> *slist,int x,int y,int w,int h)
{
    touch = t;
    display = d;
    headlist = hlist;
    subheadlist = slist;
    posX = x;
    posY = y;
    width = w;
    height = h;
}

void ListView::setPadding(int vertical,int horizontal)
{
    paddingTop = vertical;
    paddingDown = vertical;
    paddingLeft = horizontal;
    paddingRight = horizontal;
}

void ListView::setPadding(int padd)
{
    paddingTop  = padd;
    paddingDown = padd;
    paddingLeft = padd;
    paddingRight = padd;
}

void ListView::setPadding(int t,int l, int r,int d)
{
    paddingTop  = t;
    paddingDown = d;
    paddingLeft = l;
    paddingRight = r;
}

void ListView::setdividerwidth(int d)
{
    dividerWidth = d;
}

void ListView::loadView()
{        
    sprite->setColorDepth(4);
    sprite->setSwapBytes(true);
    sprite->setTextSize(1);
    sprite->setTextColor(TFT_WHITE);
    display->setTextFont(2);
    cellheight = paddingTop + paddingDown + (display->fontHeight());
    Serial.printf("%d,%d,%d",paddingTop,display->fontHeight(),paddingDown);
    sprite_height = headlist->size() * cellheight + paddingDown;
    sprite->createSprite(width,sprite_height);
    sprite->drawRect(0,0,width,sprite_height,TFT_WHITE);
    for(int i = 0;i < headlist->size();i++)
    {
        sprite->drawString(headlist->get(i),paddingLeft,(paddingTop+(cellheight*i)),2);
        sprite->drawLine(0,(cellheight*(i+1)),width,(cellheight*(i+1)),TFT_WHITE);
    }
    touch_zones = sprite_height / cellheight;
}

void ListView::show()
{
    sprite->pushSprite(posX,posY,0,0+pushspriteval,width,height);
}

void ListView::lvtouchtask()
{
    touchxsprite = touch->x - posX;
    touchysprite = touch->y - posY;
    //Serial.printf("X = %d, Y = %d \n",touch->x,touch->y);
    if(((touchysprite >= 0) && (touchysprite <= height))&&((touchxsprite >= 0)&&(touchxsprite <= width)))
    {
        if(touch->typeEvent == 5)
        {
            display->fillRect(posX,posY,width,height,TFT_BLACK);
            pushspriteval += cellheight;
            pusheditems += 1;
            touch->typeEvent = 0;
            show();
        }
        else if(touch->typeEvent == -5)
        {
            if(pushspriteval > 0)
            {
                display->fillRect(posX,posY,width,height,TFT_BLACK);
                pushspriteval -= cellheight;
                pusheditems -= 1;
                touch->typeEvent = 0;
                show();
            }
        }
        else if(touch->typeEvent == 1)
        {
            float select = ((float)touchysprite) / ((float)cellheight + 7);
            int selectedpoint = ((int)select) + pusheditems;
            Serial.printf("%d,%d,%f,%d\n",cellheight,touchysprite,select,selectedpoint);
            if(selectedpoint < touch_zones)
            {
                sprite->fillRect(0,(0 + (selectedpoint*cellheight)),width,cellheight,TFT_WHITE);
                sprite->setTextColor(TFT_BLACK);
                sprite->drawString(headlist->get(selectedpoint),paddingLeft,(paddingTop+(cellheight*selectedpoint)),2);
                sprite->setTextColor(TFT_WHITE);
                Serial.println(headlist->get(selectedpoint));
                show();
                delay(100);
                sprite->fillRect(0,(0 + (selectedpoint*cellheight)),width,cellheight,TFT_BLACK);
                loadView();
                sprite->drawString(headlist->get(selectedpoint),paddingLeft,(paddingTop+(cellheight*selectedpoint)),2);
                show();
            }
            touch->typeEvent = 0;
        }
    }
}