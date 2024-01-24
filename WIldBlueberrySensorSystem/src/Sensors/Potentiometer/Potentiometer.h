//
// Class: Potentiometer
// Description: This class defines the interface for a Potentiometer
//
#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H
#include "../Sensor.h"
class Potentiometer : public Sensor
{
    // set the sensor type to potentiometer
    SensorType getType() const override
    {
        return SensorType::POTENTIOMETER;
    }
};
#endif