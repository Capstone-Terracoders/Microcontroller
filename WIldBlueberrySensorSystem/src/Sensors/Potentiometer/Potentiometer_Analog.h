//
// Class: Potentiometer_Analog class
// Description: This class is used to read data from an analog potentiometer
//
// Pinout
//  1 - ground
//  2 - Ao aka output
//  3 - Vcc (5V)
#ifndef POTENTIOMETER_ANALOG_H
#define POTENTIOMETER_ANALOG_H
#include "Potentiometer.h"

class Potentiometer_Analog : public Potentiometer
{
public:
    // constructor
    Potentiometer_Analog(int data_pin);
    // sets the signal type to analog
    SignalType getSignalType() const override
    {
        return SignalType::ANALOG;
    }
    // destructor
    virtual ~Potentiometer_Analog();

    void setPin(int pin);

    int getPin();
    float readData() override; // This gets the potentiometer data
private:
    int _data_pin = 0;
};
#endif