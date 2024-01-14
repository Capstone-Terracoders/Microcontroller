#ifndef HallEffectSensor_US5881_h
#define HallEffectSensor_US5881_h

#include "HallEffectSensor.h"

class HallEffectSensor_US5881 : public HallEffectSensor
{
public:
    // constructor
    // const reference pass because the values w and h don't change and reference avoid the time it takes to copy large
    //   objects by value (if there were any)
    // UltrasonicSensor_HCSR04();
    HallEffectSensor_US5881(const int &pin);
    SignalType getSignalType() const override
    {
        return SignalType::DIGITAL;
    }
    // destructor
    virtual ~HallEffectSensor_US5881();

    float readData() override; // This gets the ultrasonic sensor data
    int getPin();
    void setPin(const int &pin);

private:
    int _pin = 0;
};
#endif