#include "./Sensors/UltrasonicSensor/UtlrasonicSensor_MB1010.h"

// constructor
UltrasonicSensor_MB1010::UltrasonicSensor_MB1010(const int &data_pin)
{
    this->_data_pin = data_pin;
    pinMode(this->_data_pin, INPUT); // set echo pin as input
}

// deconstructor
UltrasonicSensor_MB1010::~UltrasonicSensor_MB1010() {}

float UltrasonicSensor_MB1010::readData()
{
    return pulseIn(_data_pin, HIGH);
}

int UltrasonicSensor_MB1010::getDataPin()
{
    return this->_data_pin;
}

void UltrasonicSensor_MB1010::setDataPin(const int &pin)
{
    this->_data_pin = pin;
}
