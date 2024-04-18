//
// Class: HallEffectSensor_NJK5002C
// Description: This class is used to read data from a NJK5002C Hall Effect Sensor
//
// Pinout:
//  Blue - ground
//  Black - Vout
//  Brown - Vcc (5V)
#ifndef SRC_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_NJK5002C_H_
#define SRC_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_NJK5002C_H_
#include "HallEffectSensor.h"
class HallEffectSensor_NJK5002C : public HallEffectSensor {
 public:
    // constructor
    explicit HallEffectSensor_NJK5002C(const int &pin);
    // sets the signal type to digital
    SignalType getSignalType() const override {
        return SignalType::DIGITAL;
    }
    // destructor
    virtual ~HallEffectSensor_NJK5002C();
    // Accessors
    float readData() override;  // This gets the hall effect sensor data
    int getPin();
    // Mutators
    void setPin(const int &pin);
    // Interrupt Handlers
    void callInterrupt();
    void resetCounter();
 private:
    int _pin = 0;
    int _triggeredCount = 0;
};
#endif  // SRC_SENSORS_HALLEFFECTSENSOR_HALLEFFECTSENSOR_NJK5002C_H_
