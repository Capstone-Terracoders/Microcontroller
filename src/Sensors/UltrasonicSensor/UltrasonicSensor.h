//
// Class: UltrasonicSensor
// Description: This class defines the interface for a Ultrasonic Sensor
//
#ifndef INCLUDE_SENSORS_ULTRASONICSENSOR_ULTRASONICSENSOR_H_
#define INCLUDE_SENSORS_ULTRASONICSENSOR_ULTRASONICSENSOR_H_
#include "./Sensors/Sensor.h"
class UltrasonicSensor : public Sensor {
 public:
    SensorType getType() const override {
        return SensorType::ULTRASONIC;
    }
};
#endif  // INCLUDE_SENSORS_ULTRASONICSENSOR_ULTRASONICSENSOR_H_
