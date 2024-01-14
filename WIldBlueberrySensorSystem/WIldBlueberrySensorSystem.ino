#include "Arduino.h"
#include "src/Sensors/Potentiometer/Potentiometer_Analog.h"
void setup()
{
    int pot_pin = 2;
    Potentiometer_Analog myPot = Potentiometer_Analog(pot_pin);
 
}

void loop()
{
  Serial.begin(1920);
}