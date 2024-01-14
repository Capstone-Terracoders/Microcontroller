#include "Sensor.h"

std::string Sensor::getName()
{
    return _name;
}
std::string Sensor::getID()
{
    return _id;
}

void Sensor::setName(const std::string &name)
{
    // This identifies what the sensor is called/does
    // For example, "rake_height" or "harvester_linear_speed"
    _name = name;
}
void Sensor::setID(const std::string &id)
{
    // This identifies what specific sensor it is
    _id = id;
}
