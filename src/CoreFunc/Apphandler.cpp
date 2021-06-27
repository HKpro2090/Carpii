#include "./CoreFunc/Apphandler.h"

void homeapptask(void * para)
{
    Homeapp happ = *(Homeapp *) para;
    for(;;)
    {
        happ.homeapphandler();
        vTaskDelay(10);
    }
}

void weatherapptask(void *para)
{
    Weatherapp weapp = *(Weatherapp *) para;
    for(;;)
    {
        weapp.Weatherapphandler();
        vTaskDelay(10);
    }
}

Apphandler::Apphandler(Timeservice* tmsp,TFT_eSPI *espi,RotaryInput *rip,TouchHandler *th,Apphandler *selfaph)
{
    Laucherapptask = NULL;
    otherapprunning = false;
    services.display = espi;
    services.tmsp = tmsp;
    services.rotationinput = rip;
    services.touchinput = th;
    aph = selfaph;
    startappstruct.startapp = false;
    startappstruct.startingappname = "";
    hap = new Homeapp(services,"Homeapp",&startappstruct,&stopapp);
    weap = new Weatherapp(services,"Weatherapp",&startappstruct,&stopapp);
}

void Apphandler::startapp(char *s)
{
    Serial.println(s);
    if(top != NULL)
    {
        if(eTaskGetState(top->apptaskhandler) != eSuspended)
        {
            vTaskSuspend(top->apptaskhandler);
        }
    }
    if(strcmp(s, "Homeapp") == 0)
    {
        xTaskCreate(homeapptask,s,6000,hap,1,&Laucherapptask);
        push(Laucherapptask);
    }
    if(strcmp(s, "Weatherapp") == 0)
    {
        xTaskCreate(weatherapptask,s,1000,weap,1,&Weatherapptaskhandle);
        push(Weatherapptaskhandle);
    }
}

void Apphandler::quitapp()
{
    vTaskDelete(top->apptaskhandler);
    pop();
    vTaskResume(top->apptaskhandler);
}

void Apphandler::push(TaskHandle_t s)
{
    struct AppStackNode* temp;
    temp = new AppStackNode();
    temp->apptaskhandler = s;
    temp->link = top;
    top = temp;
}
void Apphandler::pop()
{
    struct AppStackNode* temp;
    if(top == NULL)
    {
        Serial.println("Nothing to Close");
    }
    else
    {
        temp = top;
        top = top->link;
        temp->link = NULL;
        free(temp);
    }
}

void Apphandler::appflagchecker()
{
    if(startappstruct.startapp == true)
    {
        int n = startappstruct.startingappname.length()+1;
        char newappname[n+1];
        startappstruct.startingappname.toCharArray(newappname,n);
        startapp(newappname);
        startappstruct.startapp = false;
        startappstruct.startingappname = "";
    }
    if(stopapp == true)
    {
        quitapp();
        stopapp = false;
    }
}
