//
// Class: Potentiometer
// Description: This class defines the interface for a Potentiometer
//
#ifndef SRC_SENSORS_POTENTIOMETER_POTENTIOMETER_H_
#define SRC_SENSORS_POTENTIOMETER_POTENTIOMETER_H_
#include "./Sensors/Sensor.h"
class Potentiometer : public Sensor {
    // set the sensor type to potentiometer
    SensorType getType() const override {
        return SensorType::POTENTIOMETER;
    }
};
#endif  // SRC_SENSORS_POTENTIOMETER_POTENTIOMETER_H_
