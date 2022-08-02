#include "./Apps/Weatherapp.h"

Weatherapp *wap;
bool tft_output2(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{

  if ( y >= wap->img.height() ) return 0;
  wap->img.pushImage(x, y, w, h, bitmap);
  return 1;
}

void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{
  byte seg = 6; 
  byte inc = 6;
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x0 = sx * (rx - w) + x;
  uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    wap->img.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    wap->img.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}

void Weatherapp::Weatherapphandler()
{
    // wap = this;
    // img.setSwapBytes(true);
    // TJpgDec.setCallback(tft_output2);
    // if(appscreencounter == 0)
    // {
    //     if(SD.exists(Weatherfilepath) == false)
    //     {  
    //         File myfile = SD.open(Weatherfilepath,FILE_WRITE);
    //         myfile.close();
    //         updatingweather();
    //     }
    //     else
    //     {
    //         updatingweather();
    //     }
    //     appscreencounter = 1;
    // }
    // if(appscreencounter == 1)
    // {
    //     //screenpagecounter = 0;
    //     screen1();
    // }
    // if(appservices.rotationinput->longpress)
    // {
    //     appservices.rotationinput->longpress = false;
    //     appservices.display->fillScreen(TFT_BLACK);
    //     //newstopappstruct->stopapp = true;
    //     img.deleteSprite();
    //     appscreencounter=0;
    //     screenpagecounter=1;
    //     *stopapp = true;
        
    // }

}

// void Weatherapp::updatingweather()
// {
//     HTTPClient http;
//     http.begin(serverPath);
//     int httpcode = http.GET();
//     if(httpcode > 0)
//     {
//         jsonBuffer = http.getString();
//         myobject = JSON.parse(jsonBuffer);
//     }
//     else
//     {
//         Serial.print("Error Code: ");
//         Serial.println(httpcode);
//     }
//     http.end();
//     File myfile = SD.open(Weatherfilepath,FILE_WRITE);
//     appservices.tmsp->timeupdate();
//     time_t date = mktime(&(appservices.tmsp->timeinfo));
//     String t = String(date) + "\n";
//     myfile.print(t);
//     myfile.print((jsonBuffer+"\n"));
//     myfile.close();
// }

// void Weatherapp::screen1()
// {
//     if(screenpagecounter == 0)
//     {
//         appservices.rotationinput->counter = 0;
//         bool readdata = false;
//         int i = 0;
//         String data = "";
//         File myfile = SD.open(Weatherfilepath,FILE_READ);
//         while (myfile.available())
//         {
//             char c = myfile.read();
//             if(c == '{')
//             {
//                 i++;
//                 readdata = true;
//                 data = data + c;
//                 continue;
//             }
//             if(readdata)
//             {
//                 data = data + c;
//             }
//             if(c == '}')
//             {
//                 i--;
//                 if(i == 0){
//                 myfile.close();
//                 screenpagecounter = 1;
//                 break;
//                 }
//             }
//         }
//         myobject = JSON.parse(data);
//     }
//     if(screenpagecounter == 1)
//     {
//         img.setColorDepth(8);
//         img.loadFont("Roboto-Regular-19",SD);
//         img.createSprite(213,394);

//         img.setTextColor(TFT_WHITE,TFT_BLACK);
//         img.setTextDatum(TL_DATUM);
//         img.drawString((city+","+countryCode),51,10);
//         int ftemp = myobject["main"]["feels_like"];
//         img.drawString(("Feels Like "+String(ftemp)),51,117);
//         double mintemp = myobject["main"]["temp_min"];
//         double maxtemp = myobject["main"]["temp_max"];
//         int p = myobject["main"]["pressure"];
//         const char* iconid = myobject["weather"][0]["icon"];

//         img.drawString(("Min: "+String(mintemp,2)),5,159);
//         img.drawString(("Max: "+String(maxtemp,2)),115,159);
//         img.drawString(("Pressure: "+String(p)),51,195);
//         img.drawString("m/s",140,314);

//         time_t ss = (time_t)myobject["sys"]["sunrise"];
//         time_t sr = (time_t)myobject["sys"]["sunset"];
//         localtime_r(&ss,&tmm);
//         img.drawString((String(tmm.tm_hour)+":"+String(tmm.tm_min)),45,367);
//         localtime_r(&sr,&tmm);
//         img.drawString((String(tmm.tm_hour)+":"+String(tmm.tm_min)),150,367);

//         img.unloadFont();
//         Serial.println(iconid);

//         TJpgDec.drawSdJpg(13,27,(Weathericonpath+String(iconid)+".jpg"));
//         TJpgDec.drawSdJpg(20,363,Weathersunriseicon);
//         TJpgDec.drawSdJpg(125,363,Weathersunseticon);

//         int temp = (int)myobject["main"]["temp"];
//         img.loadFont("Roboto-Bold-62",SD);
//         img.drawString(String(temp),78,50);
//         img.unloadFont();

//         img.loadFont("Roboto-Bold-19",SD);
//         img.drawString("O",147,42);
//         img.unloadFont();

//         img.loadFont("Roboto-Regular-16",SD);
//         img.drawString("Humidity",24,237);
//         img.drawString("Wind",136,237);
//         img.unloadFont();

//         img.loadFont("Roboto-Regular-29",SD);
//         img.drawString("C",161,53);
//         int hum = (int)myobject["main"]["humidity"];
//         int h = (int)map(hum,0,100,0,60);
//         img.drawString((String(hum)+" %"),28,297);
//         int wspeed = (int)myobject["wind"]["speed"];
//         int wdeg = (int)myobject["wind"]["deg"];
//         if(String(wspeed).length() == 2)
//             img.drawString(String(wspeed),142,282);
//         if(String(wspeed).length() == 1)
//             img.drawString(String(wspeed),150,282);
        
        
//         img.unloadFont();

//         fillArc(60,307,0,h,42,42,5,TFT_CYAN);
//         fillArc(158,307,wdeg - 6,6,42,42,5,TFT_GREENYELLOW);
//         fillArc(160,307,0,60,42,42,1,TFT_SILVER);
      
//         appservices.display->drawCircle(120,120,120,TFT_WHITE);
//         screenpagecounter = 2;
//     }
//     if(screenpagecounter == 2)
//     {
//         if(appservices.rotationinput->counter <= 0)
//         {
//             appservices.rotationinput->counter = 1;
//         }
//         if(appservices.rotationinput->counter >= 40)
//         {
//             appservices.rotationinput->counter = 40;
//         }
//         if(prevcount != appservices.rotationinput->counter)
//         {
//             img.pushSprite(13,13,0,appservices.rotationinput->counter*5,240,240);
//             prevcount = appservices.rotationinput->counter;
//         }
//         appservices.display->drawCircle(120,120,120,TFT_WHITE);
//     }
// }

