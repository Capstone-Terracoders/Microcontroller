//
// Class: HallEffectSensor_NJK5002C
// Description: This class is used to read data from a NJK5002C Hall Effect Sensor
//
// Pinout:
//  Blue - ground
//  Black - Vout
//  Brown - Vcc (5V)
#ifndef HallEffectSensor_NJK5002C_h
#define HallEffectSensor_NJK5002C_h
#include "HallEffectSensor.h"

class HallEffectSensor_NJK5002C : public HallEffectSensor
{
public:
    // constructor
    HallEffectSensor_NJK5002C(const int &pin);

    // sets the signal type to digital
    SignalType getSignalType() const override
    {
        return SignalType::DIGITAL;
    }
    // destructor
    virtual ~HallEffectSensor_NJK5002C();

    float readData() override; // This gets the ultrasonic sensor data
    int getPin();
    void setPin(const int &pin);

private:
    int _pin = 0;
};
#endif