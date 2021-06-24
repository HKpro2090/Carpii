#ifndef HOMEAPP_H
#define HOMEAPP_H

#include <CoreFunc/servicepointers.h>


class Homeapp
{
private:
    struct servicepointers appservices;
    int i = 0;
    int j = 0;
    char ptimeHour[3];
    char ptimeminute[3];
    char ptimesec[3];
    char ptimeday[4];
    char ptimemonth[4];
    char ptimedate[3];
    int prevcounter = 0;
public:
    Homeapp(struct servicepointers s);
    void homeapphandler();
    void homescreen();
    void menuscreen();
};
#endif
