#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h
#include "../Sensor.h"
class UltrasonicSensor : public Sensor
{
public:
    SensorType getType() const override
    {
        return SensorType::ULTRASONIC;
    }
};
#endif