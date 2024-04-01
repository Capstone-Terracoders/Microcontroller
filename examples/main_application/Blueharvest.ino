#include "Arduino.h"
#include <WildBlueberrySensorSystem.h>
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

// Sensor Information
const int DIVISIONS_OF_RAKE_WHEEL = 2;  // AKA the number of magnets on the rake
const float RADIUS_OF_RAKE_WHEEL = 0.1;  // Meters

const int DIVISIONS_OF_HARVESTER_WHEEL = 2;  // AKA the number of magnets on the rake
const float RADIUS_OF_HARVESTER_WHEEL = 0.1;  // Meters

const float HEIGHT_OF_RAKE = 0.3;  // Meters
const int MAX_VALUE_OF_RAKE_HEIGHT = 1000;  // Used for clamping sensor values
const int MIN_VALUE_OF_RAKE_HEIGHT = 0;  // Used for clamping sensor values

const float BUSH_HEIGHT_CALIBRATION_FACTOR = 1;  // calibration factor for the ultrasonic sensor

const float LENGTH_OF_RAKE_TEETH = 0.4;  //
const float ANGLE_OF_INCLINATION_OF_RAKE = 0.1;  //
// Define sensors map that holds all sensors
std::map<std::string, std::unique_ptr<Sensor>> sensors;

// Data Processing
DataProcessing dataProcessing;

// Data Interpretation
DataInterpretation dataInterpretation;

// Bluetooth Communication
BluetoothCommunication bleCommunication;
const char*  deviceName = "WildBlueberrySensorSystem";
const char*  serviceUUID = "DA00";  // Sensor Data Service
const char*  sensorDataCharacteristicUUID = "19B10001-E8F2-537E-4F6C-D104768A1214";
const char*  sensorRawDataCharacteristicUUID = "19B10001-E8F2-537E-4F6C-R104768A1214";
const char*  configurationCharacteristicUUID = "19B10001-c45f-478d-bf47-257959fedb0a";
const char*  optimalOperationCharacteristicUUID = "19B10001-O45f-478d-bf47-O104768A1214";
BLEService sensorDataService(serviceUUID);
BLEDevice central;
const int CHARACTERISTIC_BUFFER_SIZE = 255;
// Elapsed time
uint64_t elapsedTime = 0;

/// Define the sensors being used and set them up
void sensorSetup() {
  /// Define the sensors being used in this code block
  // Hall Effect Sensors
  rakeSpeedSensor.setID("Rotational Speed of the rake");  // Set the id of the sensor for idenfitication
  rakeSpeedSensor.setName("rake_rotation_speed");         // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(rakeSpeedSensor.getName(),
  std::make_unique<HallEffectSensor_NJK5002C>(rakeSpeedSensor)));

  harvesterLinearSpeedSensor.setID("Linear Speed of the harvester");  // Set the id of the sensor for idenfitication
  harvesterLinearSpeedSensor.setName("harvester_linear_speed");       // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(harvesterLinearSpeedSensor.getName(),
  std::make_unique<HallEffectSensor_NJK5002C>(harvesterLinearSpeedSensor)));

  // Ultrasonic Sensors
  bushHeightSensor.setID("Blueberry Bush Height");  // Set the id of the sensor for idenfitication
  bushHeightSensor.setName("bush_height");          // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(bushHeightSensor.getName(),
  std::make_unique<UltrasonicSensor_MB1010>(bushHeightSensor)));

  // Potentiometers
  rakeHeightSensor.setID("Rake Height");    // Set the id of the sensor for idenfitication
  rakeHeightSensor.setName("rake_height");  // Set the name of the sensor for idenfitication
  sensors.insert(std::make_pair(rakeHeightSensor.getName(),
  std::make_unique<Potentiometer_Analog>(rakeHeightSensor)));
}

// #define DEBUG
void terminalPrint(float rakeRPM, float harvesterLinearSpeed, float rakeHeight, float blueberryBushHeight, int delay) {
  if (millis() - elapsedTime > delay) {
    elapsedTime = millis();
    // This is debug code to test the functionality of sensors
    #ifdef DEBUG
    Serial.println("Rake Speed | Harvester Speed | Pot    | Ultrasonic Sensor");
    Serial.print(rakeSpeedSensor.readData(), 2);  // Prints the raw data from the RPM of the rake
    Serial.print("       |");
    Serial.print(harvesterLinearSpeedSensor.readData(), 2);  // Prints the raw data from speed of the harvester
    Serial.print("       |");
    Serial.print(rakeHeightSensor.readData(), 2);  // Prints the raw data from the rake height sensor
    Serial.print("    |");
    Serial.println(bushHeightSensor.readData(), 2);  // Prints the raw data from the blueberry bush height sensor
    #endif
    Serial.println("Rake RPM | Harvester Speed | Rake Height | Blueberry bush height");
    Serial.print(rakeRPM);  // Prints the calculated rotational speed of the rake
    Serial.print("       |");
    Serial.print(harvesterLinearSpeed);  // Prints the calculated linear speed of the harvester
    Serial.print("        |");
    Serial.print(rakeHeight);  // Prints the calculated height of the rake
    Serial.print("        |");
    Serial.println(blueberryBushHeight);  // Prints the calculated height of the rake
  }
}

void setup() {
  // Setup Serial Monitor for debugging
  Serial.begin(9600);
  Serial.println("-----------------------------Starting Wild Blueberry Sensor System-----------------------------");
  // Create BLE Communication
  bleCommunication = BluetoothCommunication(deviceName, &sensorDataService);
  // Add BLE Characteristics
  // Live Data
  bleCommunication.addCharacteristicToList(sensorDataCharacteristicUUID,
  BLERead | BLENotify, CHARACTERISTIC_BUFFER_SIZE);
  // Raw Data
  bleCommunication.addCharacteristicToList(sensorRawDataCharacteristicUUID,
  BLERead | BLENotify, CHARACTERISTIC_BUFFER_SIZE);
  // Optimal Operation data
  bleCommunication.addCharacteristicToList(optimalOperationCharacteristicUUID,
  BLERead | BLENotify, CHARACTERISTIC_BUFFER_SIZE);
  //
  bleCommunication.addCharacteristicToList(configurationCharacteristicUUID,
  BLERead | BLEWrite | BLENotify, CHARACTERISTIC_BUFFER_SIZE);
  // Setup BLE service
  bleCommunication.begin();
  // Sets up sensors defined globaly
  sensorSetup();
  dataProcessing = DataProcessing();
  dataInterpretation = DataInterpretation();
}


void loop() {
  char buffer[255];
  // Bluetooth
  BLE.poll();
  // Check for connection
  central = BLE.central();
  int debugPrintDelay = 100;
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    while (central.connected()) {
      // Data processing
      // Calculate the rotational speed of the rake
      float rawRakeSpeedSensor = rakeSpeedSensor.readData();
      float rakeRPM = dataProcessing.calculateRakeRotationalSpeed(rawRakeSpeedSensor,
      DIVISIONS_OF_RAKE_WHEEL, RADIUS_OF_RAKE_WHEEL);
      // Calculate the height of the rake
      float rawRakeHeightSensor = rakeHeightSensor.readData();
      float rakeHeight = dataProcessing.calculateRakeHeight(rawRakeHeightSensor,
      HEIGHT_OF_RAKE, MAX_VALUE_OF_RAKE_HEIGHT, MIN_VALUE_OF_RAKE_HEIGHT);
      // Calculate the height of the rake
      float rawBushHeightSensor = bushHeightSensor.readData();
      float blueberryBushHeight = dataProcessing.calculateBushHeight(rawBushHeightSensor,
      BUSH_HEIGHT_CALIBRATION_FACTOR);
      // Calculate the linear speed of the harvester
      float rawHarvesterLinearSpeedSensor = harvesterLinearSpeedSensor.readData();
      float harvesterLinearSpeed = dataProcessing.calculateHavesterLinearSpeed(
        rawHarvesterLinearSpeedSensor, DIVISIONS_OF_HARVESTER_WHEEL, RADIUS_OF_HARVESTER_WHEEL);
      // Debugging
      terminalPrint(rakeRPM, rakeHeight, blueberryBushHeight, harvesterLinearSpeed, debugPrintDelay);
      // Update BLE characteristic with sensor data
      String sensorData = "{\"RPM\": "+String(rakeRPM) + ","
      + "\"Rake Height\": " + String(rakeHeight) + ","
      + "\"Bush Height\": " +String(blueberryBushHeight) + ","
      + "\"Speed\": " +String(harvesterLinearSpeed) + "}";

      // Update BLE Characteristics
      String rawSensorData = "{\"Raw RPM\":" + String(rawRakeSpeedSensor) + ","
      + "\"Raw Rake Height\":" + String(rawRakeHeightSensor) + ","
      + "\"Raw Bush Height\":" + String(rawBushHeightSensor) + ","
      + "\"Raw Speed\":" + String(rawHarvesterLinearSpeedSensor) + "}";

      // Update the optimal Opeartion BLE Charateritic
      float optimalRakeHeight = dataInterpretation.optimalRakeHeight(blueberryBushHeight, LENGTH_OF_RAKE_TEETH,
      ANGLE_OF_INCLINATION_OF_RAKE, RADIUS_OF_RAKE_WHEEL, rakeRPM);
      float optimalRakeRotationSpeed = dataInterpretation.optimalRakeRotationSpeed(rakeHeight, blueberryBushHeight,
      rakeRPM, harvesterLinearSpeed);

      String optimalOperationData = "{\"OptRakeHeight\": "+String(optimalRakeHeight) + ","
      + "\"OptRakeRPM\": " + String(optimalRakeRotationSpeed) + "}";

      // Check if data is available to read
      bleCommunication.writeCharacteristic(sensorDataCharacteristicUUID, sensorData.c_str());
      bleCommunication.writeCharacteristic(sensorRawDataCharacteristicUUID, rawSensorData.c_str());
      bleCommunication.writeCharacteristic(optimalOperationCharacteristicUUID, optimalOperationData.c_str());
      bleCommunication.receivedDataCharacteristic(configurationCharacteristicUUID, buffer, CHARACTERISTIC_BUFFER_SIZE);
    }
    // When the central disconnects, print a message
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  } else {
      // Data processing
      // Calculate the rotational speed of the rake
      float rawRakeSpeedSensor = rakeSpeedSensor.readData();
      float rakeRPM = dataProcessing.calculateRakeRotationalSpeed(rawRakeSpeedSensor,
      DIVISIONS_OF_RAKE_WHEEL, RADIUS_OF_RAKE_WHEEL);
      // Calculate the height of the rake
      float rawRakeHeightSensor = rakeHeightSensor.readData();
      float rakeHeight = dataProcessing.calculateRakeHeight(rawRakeHeightSensor,
      HEIGHT_OF_RAKE, MAX_VALUE_OF_RAKE_HEIGHT, MIN_VALUE_OF_RAKE_HEIGHT);
      // Calculate the height of the rake
      float rawBushHeightSensor = bushHeightSensor.readData();
      float blueberryBushHeight = dataProcessing.calculateBushHeight(rawBushHeightSensor,
      BUSH_HEIGHT_CALIBRATION_FACTOR);
      // Calculate the linear speed of the harvester
      float rawHarvesterLinearSpeedSensor = harvesterLinearSpeedSensor.readData();
      float harvesterLinearSpeed = dataProcessing.calculateHavesterLinearSpeed(
        rawHarvesterLinearSpeedSensor, DIVISIONS_OF_HARVESTER_WHEEL, RADIUS_OF_HARVESTER_WHEEL);
      // Debugging
      terminalPrint(rakeRPM, rakeHeight, blueberryBushHeight, harvesterLinearSpeed, debugPrintDelay);
  }
}
