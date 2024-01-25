#include "Arduino.h"
#include "WildBlueberrySensorSystem.h"
// Define sensors pin locations
#define RAKESPEED_PIN 8
#define RAKEHEIGHT_PIN A0
#define BUSHHEIGHT_PIN A5
// Define Sensors
HallEffectSensor_NJK5002C rakeSpeedSensor = HallEffectSensor_NJK5002C(RAKESPEED_PIN);
Potentiometer_Analog rakeHeightSensor = Potentiometer_Analog(RAKEHEIGHT_PIN);
UltrasonicSensor_MB1010 bushHeightSensor = UltrasonicSensor_MB1010(BUSHHEIGHT_PIN);

// Define sensors map that holds all sensors
std::map<std::string, std::unique_ptr<Sensor>> sensors;

// Read Sensor Data
ReadSensorData readSensorData;

void setup()
{
  // Setup Serial Monitor for debugging
  Serial.begin(9600);
  Serial.println("-----------------------------Starting Wild Blueberry Sensor System-----------------------------");
  // Sets up sensors defined globably
  sensorSetup();
  // Instantiate readSensorData using the sensors map
  readSensorData = ReadSensorData(&sensors);
}

void loop()
{
  // This is debug code to test the functionality of sensors
  Serial.println("Rake Speed | Pot    | Ultrasonic Sensor");
  Serial.print(readSensorData.getRakeRotationSpeedData(), 2); // Prints the raw data from the rotational speed of the rake
  Serial.print("       |");
  Serial.print(readSensorData.getRakeHeightData(), 2); // Prints the raw data from the rake height sensor
  Serial.print("    |");
  Serial.println(readSensorData.getBushHeightData(), 2); // Prints the raw data from the blueberry bush height sensor
  delay(1000);                                           // Delays for 1000 miliseconds
}

/// Define the sensors being used and set them up
void sensorSetup()
{
  /// Define the sensors being used in this code block
  // Hall Effect Sensors
  rakeSpeedSensor.setID("Rotational Speed of the rake"); // Set the id of the sensor for idenfitication
  rakeSpeedSensor.setName("rake_rotation_speed");        // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(rakeSpeedSensor.getName(), std::make_unique<HallEffectSensor_NJK5002C>(rakeSpeedSensor)));

  // Ultrasonic Sensors
  bushHeightSensor.setID("Blueberry Bush Height"); // Set the id of the sensor for idenfitication
  bushHeightSensor.setName("bush_height");         // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(bushHeightSensor.getName(), std::make_unique<UltrasonicSensor_MB1010>(bushHeightSensor)));

  // Potentiometers
  rakeHeightSensor.setID("Rake Height");   // Set the id of the sensor for idenfitication
  rakeHeightSensor.setName("rake_height"); // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(rakeHeightSensor.getName(), std::make_unique<Potentiometer_Analog>(rakeHeightSensor)));
}