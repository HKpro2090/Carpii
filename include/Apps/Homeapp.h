#ifndef HOMEAPP_H
#define HOMEAPP_H
#include <Apps/App.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/StartAppStruct.h>
class Homeapp : public App
{
    private:
    //struct servicepointers appservices;
    char ptimeHour[3];
    char ptimeminute[3];
    char ptimesec[3];
    char ptimeday[4];
    char ptimemonth[4];
    char ptimedate[3];
    int prevcounter = 0;
    unsigned long prevtime = 0;
public:
    Homeapp(struct servicepointers s,String apname,StartAppStruct *n,bool *stopappflag):App(s,apname,n,stopappflag){};
    void homeapphandler();
    void homescreen();
    void menuscreen();
};
#endif
