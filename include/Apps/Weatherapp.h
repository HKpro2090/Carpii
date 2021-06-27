#ifndef WEATHERAPP_H
#define WEATHERAPP_H
#include <Apps/App.h>
#include <Arduino.h>
#include <CoreFunc/servicepointers.h>
#include <HTTPClient.h>



class Weatherapp : public App
{
    private:
    unsigned long prevtime = 0;
    String openWeatherMapApiKey = "20d989b8871d95e37992a0e393b27967";
    String city = "Bangalore";
    String countryCode = "IN";
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
    String jsonBuffer;
    //HttpClient http;
    public:
    Weatherapp(struct servicepointers s,String apname,StartAppStruct *n,bool *stopappflag):App(s,apname,n,stopappflag){};
    void Weatherapphandler();
    void screen1();
};
#endif