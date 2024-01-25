#ifndef ULTRASONICSENSOR_HCSR04_H
#define ULTRASONICSENSOR_HCSR04_H
#include "UltrasonicSensor.h"
class UltrasonicSensor_HCSR04 : public UltrasonicSensor
{
public:
    // constructor
    // UltrasonicSensor_HCSR04();
    UltrasonicSensor_HCSR04(const int &echo_pin, const int &trigger_pin);
    // set the signal type to digital
    SignalType getSignalType() const override
    {
        return SignalType::DIGITAL;
    }
    // destructor
    virtual ~UltrasonicSensor_HCSR04();
    // Accessors
    float readData() override; // This gets the ultrasonic sensor data
    int getEchoPin();
    int getTriggerPin();

    // Mutators
    void setEchoPin(const int &pin);
    void setTriggerPin(const int &pin);

private:
    int _echo_pin = 0;    // echo pin receives the signal
    int _trigger_pin = 1; // trigger pin transmits the signal
};
#endif