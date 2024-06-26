#include "./Sensors/HallEffectSensor/HallEffectSensor_NJK5002C.h"

// constructor
HallEffectSensor_NJK5002C::HallEffectSensor_NJK5002C(const int &pin) {
    this->_pin = pin;
    pinMode(_pin, INPUT_PULLUP);  // set pin as input pullup resistor
}

// deconstructor
HallEffectSensor_NJK5002C::~HallEffectSensor_NJK5002C() {}

float HallEffectSensor_NJK5002C::readData() {
    return digitalRead(_pin);
}

int HallEffectSensor_NJK5002C::getPin() {
    return _pin;
}

void HallEffectSensor_NJK5002C::setPin(const int &pin) {
    this->_pin = pin;
}
