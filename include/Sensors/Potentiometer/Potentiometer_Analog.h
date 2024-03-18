//
// Class: Potentiometer_Analog class
// Description: This class is used to read data from an analog potentiometer
//
// Pinout
//  1 - ground
//  2 - Ao aka output
//  3 - Vcc (5V)
#ifndef INCLUDE_SENSORS_POTENTIOMETER_POTENTIOMETER_ANALOG_H_
#define INCLUDE_SENSORS_POTENTIOMETER_POTENTIOMETER_ANALOG_H_
#include "Potentiometer.h"

class Potentiometer_Analog : public Potentiometer {
 public:
    // constructor
    explicit Potentiometer_Analog(int data_pin);
    // sets the signal type to analog
    SignalType getSignalType() const override {
        return SignalType::ANALOG;
    }
    // destructor
    virtual ~Potentiometer_Analog();
    // Mutators
    void setPin(int pin);
    // Accessors
    int getPin();
    float readData() override;  // This gets the potentiometer data
 private:
    int _data_pin = 0;
};
#endif  // INCLUDE_SENSORS_POTENTIOMETER_POTENTIOMETER_ANALOG_H_
