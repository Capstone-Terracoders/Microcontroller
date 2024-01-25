//
// Class: ReadSensorData
// Description: This class is used to read the sensor data from the sensors
//
#ifndef READSENSORDATA_H
#define READSENSORDATA_H

#include <map>
#include <memory>
#include <string>
#include "../Sensors/Sensor.h" // Include the header for the Sensor class

class ReadSensorData
{
public:
    ReadSensorData();
    ReadSensorData(std::map<std::string, std::unique_ptr<Sensor>> *sensors);
    ~ReadSensorData();

    // Accessors
    float getHarvesterLinearSpeedData();
    float getRakeRotationSpeedData();
    float getRakeHeightData();
    float getBushHeightData();

private:
    std::map<std::string, std::unique_ptr<Sensor>> *_sensors;
};

#endif