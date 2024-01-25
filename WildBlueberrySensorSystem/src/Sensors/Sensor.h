//
// Class: Sensor
// Description: This class defines the interface for a Sensor
//
#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include <iostream>

// This is the type of sensor
// Add to this list when a new sensor is created
enum class SensorType
{
    ULTRASONIC,
    HALLEFFECT,
    POTENTIOMETER,
};

// This is the type of signal used by the sensor
enum class SignalType
{
    ANALOG,
    DIGITAL,
};

class Sensor
{
public:
    // accessors
    virtual SensorType getType() const = 0;
    virtual SignalType getSignalType() const = 0;
    virtual std::string getName(); // This gets the sensor name
    virtual std::string getID();   // This gets the sensor ID
    virtual float readData() = 0;  // This gets the sensor data
    // Mutators
    virtual void setName(const std::string &name);
    virtual void setID(const std::string &id);

private:
    std::string _name;
    std::string _id;
};
#endif