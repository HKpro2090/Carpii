#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <CoreFunc/Timeservice.h>
#include "SPI.h"
#include <TFT_eSPI.h>
#include <CoreFunc/Apphandler.h>
#include <CoreFunc/RotaryInput.h>
#include <TJpg_Decoder.h>
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

Timeservice tms(19800,0);
TFT_eSPI tft = TFT_eSPI();
Timeservice* tmsp = &tms;
TFT_eSPI* display = &tft;

TFT_eSprite stext1 = TFT_eSprite(&tft);
RotaryInput *RI = new RotaryInput();
Apphandler aph(tmsp,display,RI);

TaskHandle_t wifitaskhandle;
TaskHandle_t sdtaskhandle;
TaskHandle_t touchtashandle;
TaskHandle_t rotarytaskhandle;

int graphVal = 1;
int delta = 1;
int i = 0;
bool sdenabled;
bool loading = true;
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

void setup() {
  Serial.begin(9600);
  display->init();
  display->setSwapBytes(true);
  display->setRotation(2);
  display->setCursor(55,113);
  display->fillScreen(TFT_BLACK);
  display->setTextColor(TFT_WHITE,TFT_BLACK);
  display->setTextSize(2);
  display->println(F("Loading..."));

  xTaskCreate(keepWiFiAlive,"WifiService",5000,NULL,1,&wifitaskhandle);
  xTaskCreate(sdcardintializsetask,"SD card Task",6000,NULL,1,&sdtaskhandle);

  tms.configtimezone();
  tms.timeupdate();
  
  uint16_t calData[5] = { 249, 3454, 353, 3490, 2 };
  tft.setTouch(calData);
    
  xTaskCreate(inputtask,"Rotary Input",1000,NULL,1,&rotarytaskhandle);
  display->fillScreen(TFT_BLACK);
  loading = false;
  aph.defaulttolauncher();
}

void loop() {
}