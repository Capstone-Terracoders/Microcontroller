#include "./ReadSensorData/ReadSensorData.h"
// constructor
ReadSensorData::ReadSensorData()
{
}
// constructor
ReadSensorData::ReadSensorData(std::map<std::string, std::unique_ptr<Sensor>> *sensors)
    : _sensors(sensors)
{
}
// destructor
ReadSensorData::~ReadSensorData()
{
}
// getHarvesterLinearSpeedData() returns the data from the harvester_linear_speed sensor
float ReadSensorData::getHarvesterLinearSpeedData()
{
    auto it = _sensors->find("harvester_linear_speed"); // find the sensor with the name "harvester_linear_speed"
    if (it != _sensors->end())                          // if the sensor is found
    {
        // return the data from the sensor
        return it->second->readData();
    }
    // if the sensor is not found, return 0
    return 0;
}

// getRakeRotationSpeedData() returns the data from the rake_rotation_speed sensor
float ReadSensorData::getRakeRotationSpeedData()
{
    auto it = _sensors->find("rake_rotation_speed"); // find the sensor with the name "rake_rotation_speed"
    if (it != _sensors->end())                       // if the sensor is found
    {
        // return the data from the sensor
        return it->second->readData();
    }
    // if the sensor is not found, return 0
    return 0;
}

// getRakeHeightData() returns the data from the rake_height sensor
float ReadSensorData::getRakeHeightData()
{
    auto it = _sensors->find("rake_height"); // find the sensor with the name "rake_height"
    if (it != _sensors->end())               // if the sensor is found
    {
        // return the data from the sensor
        return it->second->readData();
    }
    // if the sensor is not found, return 0
    return 0;
}

// getBushHeightData() returns the data from the bush_height sensor
float ReadSensorData::getBushHeightData()
{
    auto it = _sensors->find("bush_height"); // find the sensor with the name "bush_height"
    if (it != _sensors->end())               // if the sensor is found
    {
        // return the data from the sensor
        return it->second->readData();
    }
    // if the sensor is not found, return 0
    return 0;
}