#ifndef WEATHERAPP_H
#define WEATHERAPP_H
#include <Apps/App.h>
#include <Arduino.h>
#include <CoreFunc/servicepointers.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#define DEG2RAD 0.0174532925
class Weatherapp : public App
{
    private:
    unsigned long prevtime = 0;
    String openWeatherMapApiKey = "20d989b8871d95e37992a0e393b27967";
    String city = "Bangalore";
    String countryCode = "IN";
    String serverPath = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey + "&units=metric";
    String jsonBuffer;
    JSONVar myobject;
    String Weatherfilepath = "/WeatherAppFiles/Weatherinfo.txt";
    String Weatherfontpath = "WeatherAppFiles/Fonts/";
    String Weathericonpath = "/WeatherAppFiles/Icons/";
    String Weathersunriseicon = "/WeatherAppFiles/Sunrise.jpg";
    String Weathersunseticon = "/WeatherAppFiles/Sunset.jpg";
    int prevcount;
    struct tm tmm;
    TaskHandle_t Weatherupdatetaskhandle;
    public:
    TFT_eSprite img = TFT_eSprite(appservices.display);
    Weatherapp(struct servicepointers s,String apname,StartAppStruct *n,bool *stopappflag):App(s,apname,n,stopappflag){};
    void Weatherapphandler();
    void screen1();
    void updatingweather();
    void testfunction();
};
#endif