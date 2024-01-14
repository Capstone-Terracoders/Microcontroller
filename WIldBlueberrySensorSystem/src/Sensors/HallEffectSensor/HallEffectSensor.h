#ifndef HALLEFFECTSENSOR_H
#define HALLEFFECTSENSOR_H
#include "../Sensor.h"
class HallEffectSensor : public Sensor
{
public:
    SensorType getType() const override
    {
        return SensorType::HALLEFFECT;
    }
};
#endif