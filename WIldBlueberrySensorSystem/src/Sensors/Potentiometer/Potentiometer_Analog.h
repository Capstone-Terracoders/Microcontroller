#ifndef POTENTIOMETER_ANALOG_H
#define POTENTIOMETER_ANALOG_H
#include "Potentiometer.h"

class Potentiometer_Analog : public Potentiometer
{
public:
    Potentiometer_Analog(int data_pin);

    SignalType getSignalType() const override
    {
        return SignalType::ANALOG;
    }
    // destructor
    virtual ~Potentiometer_Analog();

    void setPin(int pin);

    int getPin();
    float readData() override; // This gets the hall effect sensor data

private:
    int _data_pin = 0;
};
#endif