#include "./CoreFunc/RotaryInput.h"

RotaryInput::RotaryInput()
{
  pinMode(ROTARY_ENCODER_CLK,INPUT);
  pinMode(ROTARY_ENCODER_DT,INPUT);
  pinMode(ROTARY_ENCODER_SW,INPUT_PULLUP);
  lastStateCLK = digitalRead(ROTARY_ENCODER_CLK);
}

void RotaryInput::rotaryRotation()
{
  currentStateCLK = digitalRead(ROTARY_ENCODER_CLK);
  if(currentStateCLK != lastStateCLK && currentStateCLK == 1)
  {
    if(digitalRead(ROTARY_ENCODER_DT) != currentStateCLK)
    {
      counter --;
      currentDir = "CCW";
    }
    else
    {
      counter ++;
      currentDir = "CW";
    }
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }
  lastStateCLK = currentStateCLK;
  int btnState = digitalRead(ROTARY_ENCODER_SW);
  if(btnState == LOW)
  {
    if(millis() - lastButtonPress > 50)
    {
      Serial.println(F("Button Pressed!"));
      buttonpress = true;
    }
    lastButtonPress = millis();
  }
  vTaskDelay(1);
}
int RotaryInput::returnrotatopncounter()
{
  return counter;
}