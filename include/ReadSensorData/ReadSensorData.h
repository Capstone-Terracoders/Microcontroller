//
// Class: ReadSensorData
// Description: This class is used to read the sensor data from the sensors
//
#ifndef INCLUDE_READSENSORDATA_READSENSORDATA_H_
#define INCLUDE_READSENSORDATA_READSENSORDATA_H_
#include <map>
#include <memory>
#include <string>
#include "./Sensors/Sensor.h"  // Include the header for the Sensor class
class ReadSensorData {
 public:
    // Constructors
    ReadSensorData();
    explicit ReadSensorData(std::map<std::string, std::unique_ptr<Sensor>> *sensors);
    // Destructor
    ~ReadSensorData();
    // Accessors
    float getHarvesterLinearSpeedData();
    float getRakeRotationSpeedData();
    float getRakeHeightData();
    float getBushHeightData();

 private:
    std::map<std::string, std::unique_ptr<Sensor>> *_sensors;
};
#endif  // INCLUDE_READSENSORDATA_READSENSORDATA_H_
