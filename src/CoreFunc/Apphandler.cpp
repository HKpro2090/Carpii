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

Apphandler::Apphandler(Timeservice* tmsp,TFT_eSPI *espi,RotaryInput *rip,TouchHandler *th)
{
    Laucherapptask = NULL;
    otherapprunning = false;
    services.display = espi;
    services.tmsp = tmsp;
    services.rotationinput = rip;
    services.touchinput = th;
    hap = new Homeapp(services);
}

void Apphandler::defaulttolauncher()
{
    if((Laucherapptask == NULL)&&(otherapprunning == false))
    {
        xTaskCreate(homeapptask,"Homeapp",5000,hap,1,&Laucherapptask);
    }
}
