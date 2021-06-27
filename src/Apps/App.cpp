#include "./Apps/App.h"

App::App(servicepointers s,String apname,StartAppStruct *n,bool *stopappflag)
{
    appservices.display = s.display;
    appservices.tmsp = s.tmsp;
    appservices.touchinput = s.touchinput;
    appservices.rotationinput = s.rotationinput;
    newappstruct = n;
    stopapp = stopappflag;
    Appname = apname;
}
String App::getappname()
{
    if(Appname != "");
        return Appname;
}