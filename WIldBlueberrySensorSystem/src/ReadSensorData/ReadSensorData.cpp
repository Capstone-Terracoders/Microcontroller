#include "ReadSensorData.h"

ReadSensorData::ReadSensorData()
{
}
ReadSensorData::ReadSensorData(std::map<std::string, std::unique_ptr<Sensor>> *sensors)
    : _sensors(sensors)
{
}

ReadSensorData::~ReadSensorData()
{
}

float ReadSensorData::getHarvesterLinearSpeedData()
{
    auto it = _sensors->find("harvester_linear_speed");
    if (it != _sensors->end())
    {
        return it->second->readData();
    }
    return 0;
}

float ReadSensorData::getRakeRotationSpeedData()
{
    auto it = _sensors->find("rake_rotation_speed");
    if (it != _sensors->end())
    {
        return it->second->readData();
    }
    return 0;
}

float ReadSensorData::getRakeHeightData()
{
    auto it = _sensors->find("rake_height");
    if (it != _sensors->end())
    {
        return it->second->readData();
    }
    return 0;
}

float ReadSensorData::getBushHeightData()
{
    auto it = _sensors->find("bush_height");
    if (it != _sensors->end())
    {
        return it->second->readData();
    }
    return 0;
}
