#include "Arduino.h"
#include "WildBlueberrySensorSystem.h"
#define RAKESPEED_PIN 8
#define RAKEHEIGHT_PIN A0
// Sensors
HallEffectSensor_NJK5002C rakeSpeedSensor = HallEffectSensor_NJK5002C(RAKESPEED_PIN);
Potentiometer_Analog rakeHeightSensor = Potentiometer_Analog(RAKEHEIGHT_PIN);

std::map<std::string, std::unique_ptr<Sensor>> sensors;

// Read Sensor Data
ReadSensorData readSensorData;

void setup()
{
  Serial.begin(9600);
  Serial.println("-----------------------------Start demo-----------------------------");
  // pinMode(8, INPUT_PULLUP);
  sensorSetup();
  readSensorData = ReadSensorData(&sensors);
}

void loop()
{
  int potVal = analogRead(A0);
  Serial.print("Rake Speed: ");
  Serial.println(readSensorData.getRakeRotationSpeedData());
  Serial.print("Pot: ");
  Serial.println(readSensorData.getRakeHeightData());
  delay(1000);
}

// Define the sensors being used and set them up
void sensorSetup()
{
  // Define the sensors being used in this code block

  // Hall Effect Sensors
  sensors.insert(std::make_pair("rake_rotation_speed", std::make_unique<HallEffectSensor_NJK5002C>(rakeSpeedSensor)));

  // Ultrasonic Sensors

  // Potentiometers
  sensors.insert(std::make_pair("rake_height", std::make_unique<Potentiometer_Analog>(rakeHeightSensor)));
}