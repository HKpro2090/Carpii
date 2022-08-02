#include <Arduino.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <SPIFFS.h>
#include <CoreFunc/WifiService.h>
#include <CoreFunc/TouchHandler.h>
#include <CoreFunc/Timeservice.h>
#include <CoreFunc/Apphandler.h>
#include <CoreFunc/Keyboard.h>

//Intialize Display Library
Timeservice tms(19800,0);
Timeservice* tmsp = &tms;

// RotaryInput *RI = new RotaryInput();
TFT_eSPI tft = TFT_eSPI();
TFT_eSPI* display = &tft;
TFT_eSprite img = TFT_eSprite(display);
WifiService wifiserv = WifiService(display);
TouchHandler *th = new TouchHandler(display);
Apphandler aph(tmsp,display,th,&aph);
TFT_eSPI_Button trial;
Keyboard *keyboard = new Keyboard(display,th);
#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

// TaskHandle_t touchtashandle;

// void touchtask(void *para)
// {
//   for(;;)
//   {
//     th->touchtask();
//     vTaskDelay(1);
//   }
// }

void touchtask()
{
    th->touchtask();
    // th->tevent->pollTouchScreen();
}

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

void setup(){
    //Start Display
    display->begin();
    display->setSwapBytes(true);
    display->setRotation(2);
    display->fillScreen(TFT_BLACK);
    // display->setCursor(55,113);
    display->setCursor(0,0);
    display->setTextColor(TFT_WHITE,TFT_BLACK);
    display->setTextSize(1);
    display->println(F("Loading..."));
    //Serial Debugger
    Serial.begin(9600);
    display->println(F("Serial Debugger Established"));

    //file system enable
    display->println(F("Mounting FileSystem ...."));
    if(!SPIFFS.begin(true)){
        display->println(F("An Error has occurred while mounting SPIFFS"));
  }
  else{
      display->println(F("Filesystem Mounted"));
  }
  delay(1000);
  //tms.configtimezone();
  //tms.timeupdate();
  //Wifi Service Established
  // wifiserv.bootwifi();
  touch_calibrate();
  // display->println(F("Touch Starting..."));
  // xTaskCreate(touchtask,"Touch Task",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  // display->println(F("Touch Started. See Serial Debugging for more info"));
  
  display->fillScreen(TFT_BLACK);
  // trial.initButton(&tft,100,100,50,50,TFT_WHITE,TFT_CYAN,TFT_BLACK,"Hello",1);
  // trial.drawButton();
}

void loop(){
  keyboard->keyboardtaskhandler();
  // touchtask();
  th->tevent->pollTouchScreen();
  if(th->pressed && trial.contains(th->x,th->y) && th->typeEvent == 3){
    trial.press(true);
  }
  else{
    trial.press(false);
  }

  if(trial.justReleased())
    trial.drawButton();
  if(trial.justPressed())
  {
    trial.drawButton(true);
    Serial.println("Button Clicked");
  }
}