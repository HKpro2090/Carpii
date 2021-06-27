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
  rotarybutton();
  vTaskDelay(1);
}
void RotaryInput::rotarybutton()
{
  currentState = digitalRead(ROTARY_ENCODER_SW);

  if(lastState == HIGH && currentState == LOW)
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) 
  { 
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if( pressDuration < SHORT_PRESS_TIME )
    {
      shortpress = true;
      longpress = false;
    }

    if( pressDuration > LONG_PRESS_TIME )
    {
      shortpress = false;
      longpress = true;
    }
  }
  lastState = currentState;
}