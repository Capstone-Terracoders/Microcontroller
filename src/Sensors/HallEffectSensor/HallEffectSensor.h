//
// Class: HallEffectSensor
// Description: This class defines the interface for a Hall Effect Sensor
//
#ifndef SRC_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_H_
#define SRC_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_H_
#include "./Sensors/Sensor.h"
class HallEffectSensor : public Sensor {
 public:
    SensorType getType() const override {
        return SensorType::HALLEFFECT;
    }
};
#endif  // SRC_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_H_
