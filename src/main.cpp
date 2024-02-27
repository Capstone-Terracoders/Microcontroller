#include "Arduino.h"
#include "WildBlueberrySensorSystem.h"
#include "ArduinoBLE.h"
// Define sensors pin locations
#define RAKESPEED_PIN 8
#define HARVESTERSPEED_PIN 9
#define RAKEHEIGHT_PIN A0
#define BUSHHEIGHT_PIN 7

// Define Sensors
HallEffectSensor_NJK5002C rakeSpeedSensor = HallEffectSensor_NJK5002C(RAKESPEED_PIN);
HallEffectSensor_NJK5002C harvesterLinearSpeedSensor = HallEffectSensor_NJK5002C(HARVESTERSPEED_PIN);
Potentiometer_Analog rakeHeightSensor = Potentiometer_Analog(RAKEHEIGHT_PIN);
UltrasonicSensor_MB1010 bushHeightSensor = UltrasonicSensor_MB1010(BUSHHEIGHT_PIN);

// Define sensors map that holds all sensors
std::map<std::string, std::unique_ptr<Sensor>> sensors;

// Read Sensor Data
ReadSensorData readSensorData;

// Data Processing
DataProcessing dataProcessing;

// Bluetooth Communication
BluetoothCommunication bleCommunication;
const char*  deviceName = "WildBlueberrySensorSystem";
const char*  serviceUUID = "DA00"; // Sensor Data Service
const char*  sensorDataCharacteristicUUID = "19B10001-E8F2-537E-4F6C-D104768A1214";
const char*  sensorRawDataCharacteristicUUID = "19B10001-E8F2-537E-4F6C-R104768A1214";
const char*  configurationCharacteristicUUID = "19B10001-c45f-478d-bf47-257959fedb0a";
BLEService sensorDataService(serviceUUID);
// Elapsed time 
unsigned long int dt = 0;

/// Define the sensors being used and set them up
void sensorSetup()
{
  /// Define the sensors being used in this code block
  // Hall Effect Sensors
  rakeSpeedSensor.setID("Rotational Speed of the rake"); // Set the id of the sensor for idenfitication
  rakeSpeedSensor.setName("rake_rotation_speed");        // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(rakeSpeedSensor.getName(), std::make_unique<HallEffectSensor_NJK5002C>(rakeSpeedSensor)));

  harvesterLinearSpeedSensor.setID("Linear Speed of the harvester"); // Set the id of the sensor for idenfitication
  harvesterLinearSpeedSensor.setName("harvester_linear_speed");     // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(harvesterLinearSpeedSensor.getName(), std::make_unique<HallEffectSensor_NJK5002C>(harvesterLinearSpeedSensor)));

  // Ultrasonic Sensors
  bushHeightSensor.setID("Blueberry Bush Height"); // Set the id of the sensor for idenfitication
  bushHeightSensor.setName("bush_height");         // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(bushHeightSensor.getName(), std::make_unique<UltrasonicSensor_MB1010>(bushHeightSensor)));

  // Potentiometers
  rakeHeightSensor.setID("Rake Height");   // Set the id of the sensor for idenfitication
  rakeHeightSensor.setName("rake_height"); // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(rakeHeightSensor.getName(), std::make_unique<Potentiometer_Analog>(rakeHeightSensor)));
}

// #define DEBUG
void terminalPrint(float rakeRPM, float harvesterLinearSpeed, float rakeHeight, float blueberryBushHeight){
  if (millis() - dt > 1000)
  {
    dt = millis();
    // This is debug code to test the functionality of sensors 
    #ifdef DEBUG
    Serial.println("Rake Speed | Harvester Speed | Pot    | Ultrasonic Sensor");
    Serial.print(readSensorData.getRakeRotationSpeedData(), 2); // Prints the raw data from the rotational speed of the rake
    Serial.print("       |");
    Serial.print(readSensorData.getHarvesterLinearSpeedData(), 2); // Prints the raw data from the linear speed of the harvester
    Serial.print("       |");
    Serial.print(readSensorData.getRakeHeightData(), 2); // Prints the raw data from the rake height sensor
    Serial.print("    |");
    Serial.println(readSensorData.getBushHeightData(), 2); // Prints the raw data from the blueberry bush height sensor
    
    #endif
    Serial.println("Rake RPM | Harvester Speed | Rake Height | Blueberry bush height");
    Serial.print(rakeRPM); // Prints the calculated rotational speed of the rake
    Serial.print("       |");
    Serial.print(harvesterLinearSpeed); // Prints the calculated linear speed of the harvester
    Serial.print("        |");
    Serial.print(rakeHeight); // Prints the calculated height of the rake
    Serial.print("        |");
    Serial.println(blueberryBushHeight); // Prints the calculated height of the rake
  }                      
}

void setup()
{
  // Setup Serial Monitor for debugging
  Serial.begin(9600);
  Serial.println("-----------------------------Starting Wild Blueberry Sensor System-----------------------------");
  
  // Create BLE Communication
  bleCommunication = BluetoothCommunication(deviceName, &sensorDataService);
  // Add BLE Characteristics 
  //Live Data
  bleCommunication.addCharacteristicToList(sensorDataCharacteristicUUID, BLERead | BLENotify, 255);
  //Raw Data
  bleCommunication.addCharacteristicToList(sensorRawDataCharacteristicUUID, BLERead | BLENotify, 255);
  //
  bleCommunication.addCharacteristicToList(configurationCharacteristicUUID, BLERead | BLEWrite | BLENotify, 255);

  // Setup BLE service
  bleCommunication.begin();

  // Sets up sensors defined globably
  sensorSetup();
  // Instantiate readSensorData using the sensors map
  readSensorData = ReadSensorData(&sensors);
  dataProcessing = DataProcessing();
}


void loop()
{
  // Check for connection 

  // Data processing
  float rakeRPM = dataProcessing.calculateRakeRotationalSpeed(readSensorData.getRakeRotationSpeedData(), 1, 0.1);  // Calculate the rotational speed of the rake
  float rakeHeight = dataProcessing.calculateRakeHeight(readSensorData.getRakeHeightData(), 0.3, 1000, 0); // Calculate the height of the rake
  float blueberryBushHeight = dataProcessing.calculateBushHeight(readSensorData.getBushHeightData(), 1); // Calculate the height of the rake
  float harvesterLinearSpeed = dataProcessing.calculateHavesterLinearSpeed(readSensorData.getHarvesterLinearSpeedData(), 1, 0.2); // Calculate the linear speed of the harvester
  // Debugging
  terminalPrint(rakeRPM, rakeHeight, blueberryBushHeight, harvesterLinearSpeed);
  // Update BLE characteristic with sensor data
  String sensorData = "{\"RPM\": "+String(rakeRPM) + "," 
  + "\"Rake Height\": " + String(rakeHeight) + "," 
  + "\"Bush Height\": " +String(blueberryBushHeight) + "," 
  + "\"Speed\": " +String(harvesterLinearSpeed) + "}";
  
  // Update BLE Characteristics 
  String rawSensorData = "{\"Raw RPM\":" + String(readSensorData.getRakeRotationSpeedData()) + "," 
  + "\"Raw Rake Height\":" + String(readSensorData.getRakeHeightData()) + "," 
  + "\"Raw Bush Height\":" + String(readSensorData.getBushHeightData()) + "," 
  + "\"Raw Speed\":" + String(readSensorData.getHarvesterLinearSpeedData()) + "}"; 
  char buffer[255];
  // Bluetooth
  BLE.poll();
  bleCommunication.writeCharacteristic(sensorDataCharacteristicUUID, sensorData.c_str());
  bleCommunication.writeCharacteristic(sensorRawDataCharacteristicUUID, rawSensorData.c_str());
  Serial.println(bleCommunication.receiveCharacteristic(configurationCharacteristicUUID, buffer, 255));
}
