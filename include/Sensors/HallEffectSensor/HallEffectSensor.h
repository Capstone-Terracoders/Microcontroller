//
// Class: HallEffectSensor
// Description: This class defines the interface for a Hall Effect Sensor
//
#ifndef HALLEFFECTSENSOR_H
#define HALLEFFECTSENSOR_H
#include "./Sensors/Sensor.h"
class HallEffectSensor : public Sensor
{
public:
    SensorType getType() const override
    {
        return SensorType::HALLEFFECT;
    }
};
#endif