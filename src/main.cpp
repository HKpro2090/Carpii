#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <CoreFunc/Timeservice.h>
#include "SPI.h"
#include <TFT_eSPI.h>
#include <CoreFunc/Apphandler.h>
#include <CoreFunc/RotaryInput.h>
#include <TJpg_Decoder.h>
#include <CoreFunc/TouchHandler.h>
#define FS_NO_GLOBALS

#include <FS.h>
#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif

#define SD_CS 5

#define WIFI_NETWORK "005_fast"
#define WIFI_PASSWORD "005thisisourwifigetout12345"
#define WIFI_TIMEOUT_MS 20000 
#define WIFI_RECOVER_TIME_MS 30000
#define SD_TIMEOUT_MS 2000
#define SD_RECOVER_TIME_MS 3000
#define TIRQ_PIN  39
#define CS_PIN  21 

Timeservice tms(19800,0);
TFT_eSPI tft = TFT_eSPI();
Timeservice* tmsp = &tms;
TFT_eSPI* display = &tft;

TFT_eSprite stext1 = TFT_eSprite(&tft);
RotaryInput *RI = new RotaryInput();
TouchHandler *th = new TouchHandler();
Apphandler aph(tmsp,display,RI,th,&aph);
char test[210];


TaskHandle_t wifitaskhandle;
TaskHandle_t touchtashandle;
TaskHandle_t rotarytaskhandle;

int graphVal = 1;
int delta = 1;
int i = 0;
bool sdenabled;
bool loading = true;
uint16_t x = 0, y = 0;
void keepWiFiAlive(void * parameter){
    for(;;){
        if(WiFi.status() == WL_CONNECTED){
            vTaskDelay(10000 / portTICK_PERIOD_MS);
            continue;
        }

        Serial.println(F("[WIFI] Connecting"));
        WiFi.mode(WIFI_STA);
        delay(2000);
        WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

        unsigned long startAttemptTime = millis();

        while (WiFi.status() != WL_CONNECTED && 
                millis() - startAttemptTime < WIFI_TIMEOUT_MS){}

        if(WiFi.status() != WL_CONNECTED){
            Serial.println(F("[WIFI] FAILED"));
            vTaskDelay(WIFI_RECOVER_TIME_MS / portTICK_PERIOD_MS);
			  continue;
        }

        Serial.println(F("[WIFI] Connected"));
        Serial.println(WiFi.localIP());
    }
}

void inputtask(void *parameter)
{
    for(;;)
        RI->rotaryRotation();
}

void sdcardintializsetask(void *parameter)
{
  for(;;)
  {
    //sdenabled = SD.begin(SD_CS);
    if(sdenabled)
    {
      vTaskDelete(NULL);
      continue;
    }
    Serial.println(F("Intitalizing SD Card ..."));
    sdenabled = SD.begin(SD_CS);
    delay(200);
    unsigned long startAttemptTime = millis();
    while(sdenabled != true && millis() - startAttemptTime < SD_TIMEOUT_MS){}

    if(sdenabled != true)
    {
      Serial.println(F("SD Failed"));
      vTaskDelay(SD_RECOVER_TIME_MS / portTICK_PERIOD_MS);
      continue;
    }
    Serial.println(F("SD Card Intialized"));
  }
}

void touchtask(void *para)
{
  for(;;)
  {
    th->touchtask();
    vTaskDelay(30);
  }
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  if ( y >= tft.height() ) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void apphandlerimptask(void *para)
{
  for(;;)
  {
    aph.appflagchecker();
    vTaskDelay(1);
  }
}

void setup() {
  Serial.begin(9600);

  digitalWrite(21, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(5, HIGH);
  display->begin();
  display->setSwapBytes(true);
  display->setRotation(2);
  display->setCursor(55,113);
  display->fillScreen(TFT_BLACK);
  display->setTextColor(TFT_WHITE,TFT_BLACK);
  display->setTextSize(2);
  display->println(F("Loading..."));
  xTaskCreate(keepWiFiAlive,"WifiService",5000,NULL,5,&wifitaskhandle);

  
  xTaskCreate(sdcardintializsetask,"SD Card Task",6000,NULL,2,NULL);
  tms.configtimezone();
  tms.timeupdate();
    
  xTaskCreate(inputtask,"Rotary Input",1000,NULL,1,&rotarytaskhandle);
  xTaskCreate(touchtask,"Touch Task",1000,NULL,1,NULL);
  TJpgDec.setCallback(tft_output);
  TJpgDec.setJpgScale(1);
  xTaskCreate(apphandlerimptask,"Apphandler",1000,NULL,1,NULL);
  delay(5);
  display->fillScreen(TFT_BLACK);
  loading = false;
  aph.startapp("Homeapp");
  
}

void loop() {
}