#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include <iostream>

enum class SensorType
{
    ULTRASONIC,
    HALLEFFECT,
    POTENTIOMETER,
};

enum class SignalType
{
    ANALOG,
    DIGITAL,
};

class Sensor
{
public:
    // Mutators
    virtual SensorType getType() const = 0;
    virtual SignalType getSignalType() const = 0;
    virtual std::string getName();
    virtual std::string getID();
    virtual float readData() = 0; // This gets the sensor data
    // accessors
    virtual void setName(const std::string &name);
    virtual void setID(const std::string &id);

private:
    std::string _name;
    std::string _id;
};
#endif