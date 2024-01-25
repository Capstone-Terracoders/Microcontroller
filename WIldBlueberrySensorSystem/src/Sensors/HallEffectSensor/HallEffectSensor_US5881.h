//
// Class: HallEffectSensor_US5881
// Description: This class is used to read data from a US5881 Hall Effect Sensor
//
#ifndef HallEffectSensor_US5881_h
#define HallEffectSensor_US5881_h

#include "HallEffectSensor.h"

class HallEffectSensor_US5881 : public HallEffectSensor
{
public:
    // constructor
    HallEffectSensor_US5881(const int &pin);

    // sets the signal type to digital
    SignalType getSignalType() const override
    {
        return SignalType::DIGITAL;
    }
    // destructor
    virtual ~HallEffectSensor_US5881();
    // Accessors
    float readData() override; // This gets the ultrasonic sensor data
    int getPin();

    // Mutators
    void setPin(const int &pin);

private:
    int _pin = 0;
};
#endif