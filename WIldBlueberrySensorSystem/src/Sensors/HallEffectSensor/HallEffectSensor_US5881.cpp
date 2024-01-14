#include "HallEffectSensor_US5881.h"
#include "Arduino.h"

HallEffectSensor_US5881::HallEffectSensor_US5881(const int &pin)
{
    this->_pin = pin;
    pinMode(_pin, INPUT);
}

// deconstructor
HallEffectSensor_US5881::~HallEffectSensor_US5881() {}

float HallEffectSensor_US5881::readData()
{
    return digitalRead(_pin);
}

int HallEffectSensor_US5881::getPin()
{
    return _pin;
}

void HallEffectSensor_US5881::setPin(const int &pin)
{
    this->_pin = pin;
}
