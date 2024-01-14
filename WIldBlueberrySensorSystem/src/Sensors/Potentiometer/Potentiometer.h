#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H
#include "../Sensor.h"
class Potentiometer : public Sensor
{
    SensorType getType() const override
    {
        return SensorType::POTENTIOMETER;
    }
};
#endif