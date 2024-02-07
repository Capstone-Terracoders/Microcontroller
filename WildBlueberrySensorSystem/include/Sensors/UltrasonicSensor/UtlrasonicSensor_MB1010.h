//
// Class: UtrasonicSensor_MB1010 class
// Description: This class is used to read data from the MB1010 ultrasonic sensor
// Note: Manufacturer: MaxBotix Inc. suggests to not attempt to read objects within 6 inches of the sensor
// Additionally, this sensor offers multiple modes for reading data. This class will only use the analog mode.
// In the future, implement each mode using a #ifdef statement to allow for the user to choose which mode to use.
// Specs:
// For analog 5V yields ~9.8mV/inch
// Baud rate: 9600
// Voltage: 5V
// Amperage: 2mA
// Range: 0m - 6.45m
// Rate: 20 Hz
// Pinout
//  Red     - ground
//  Brown   - Vcc (5V)
//  Black   - Tx (transmit)
//  White   - Rx (read)
//  Gray    - AN (analog)
//  Purple  - PW (pulse width)
//  Blue    - BW ()
#ifndef UltrasonicSensor_MB1010_H
#define UtlrasonicSensor_MB1010_H

#include "UltrasonicSensor.h"
class UltrasonicSensor_MB1010 : public UltrasonicSensor
{
public:
    // constructor
    // UltrasonicSensor_MB1010();
    UltrasonicSensor_MB1010(const int &data_pin);

    // set the signal type to digital
    SignalType getSignalType() const override
    {
        return SignalType::ANALOG;
    }

    // destructor
    virtual ~UltrasonicSensor_MB1010();

    float readData() override; // This gets the ultrasonic sensor data
    int getDataPin();

    void setDataPin(const int &pin);

private:
    int _data_pin = A5; // echo pin receives the signal
};
#endif
