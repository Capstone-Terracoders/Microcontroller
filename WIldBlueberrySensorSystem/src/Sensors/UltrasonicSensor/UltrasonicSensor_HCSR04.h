#ifndef ULTRASONICSENSOR_HCSR04_H
#define ULTRASONICSENSOR_HCSR04_H
#include "UltrasonicSensor.h"
class UltrasonicSensor_HCSR04 : public UltrasonicSensor
{
public:
    // constructor
    // const reference pass because the values w and h don't change and reference avoid the time it takes to copy large
    //   objects by value (if there were any)
    // UltrasonicSensor_HCSR04();
    UltrasonicSensor_HCSR04(const int &echo_pin, const int &trigger_pin);
    SignalType getSignalType() const override
    {
        return SignalType::DIGITAL;
    }
    // destructor
    virtual ~UltrasonicSensor_HCSR04();

    float readData() override; // This gets the ultrasonic sensor data
    int getEchoPin();
    int getTriggerPin();

    void setEchoPin(const int &pin);
    void setTriggerPin(const int &pin);

private:
    int _echo_pin = 0;
    int _trigger_pin = 1;
};
#endif
