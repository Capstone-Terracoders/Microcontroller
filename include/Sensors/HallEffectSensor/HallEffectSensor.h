//
// Class: HallEffectSensor
// Description: This class defines the interface for a Hall Effect Sensor
//
#ifndef INCLUDE_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_H_
#define INCLUDE_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_H_
#include "./Sensors/Sensor.h"
class HallEffectSensor : public Sensor {
 public:
    SensorType getType() const override {
        return SensorType::HALLEFFECT;
    }
};
#endif  // INCLUDE_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_H_
