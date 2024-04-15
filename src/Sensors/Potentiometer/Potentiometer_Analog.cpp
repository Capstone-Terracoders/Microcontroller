#include "./Sensors/Potentiometer/Potentiometer_Analog.h"
// constructor
Potentiometer_Analog::Potentiometer_Analog(int pin) : _data_pin(pin) {
    pinMode(pin, INPUT);
}

// deconstructor
Potentiometer_Analog::~Potentiometer_Analog() {}

float Potentiometer_Analog::readData() {
    return analogRead(_data_pin);
}

int Potentiometer_Analog::getPin() {
    return _data_pin;
}

void Potentiometer_Analog::setPin(int pin) {
    this->_data_pin = pin;
}
