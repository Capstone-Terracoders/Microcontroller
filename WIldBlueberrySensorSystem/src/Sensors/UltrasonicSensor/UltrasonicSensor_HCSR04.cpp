#include "UltrasonicSensor_HCSR04.h"
UltrasonicSensor_HCSR04::UltrasonicSensor_HCSR04(const int &echo_pin, const int &trigger_pin)
{
    _echo_pin = echo_pin;
    _trigger_pin = trigger_pin;
    pinMode(_trigger_pin, OUTPUT);
    pinMode(_echo_pin, INPUT);
}

// deconstructor
UltrasonicSensor_HCSR04::~UltrasonicSensor_HCSR04() {}

float UltrasonicSensor_HCSR04::readData()
{
    pinMode(_trigger_pin, OUTPUT);
    digitalWrite(_trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger_pin, LOW);
    pinMode(_echo_pin, INPUT);
    long duration = pulseIn(_echo_pin, HIGH); // time of flight in microseconds
    // float distance = duration * 0.0343 / 2;
    return duration;
}

int UltrasonicSensor_HCSR04::getEchoPin()
{
    return _echo_pin;
}
int UltrasonicSensor_HCSR04::getTriggerPin()
{
    return _trigger_pin;
}

void UltrasonicSensor_HCSR04::setEchoPin(const int &pin)
{
    _echo_pin = pin;
}
void UltrasonicSensor_HCSR04::setTriggerPin(const int &pin)
{
    _trigger_pin = pin;
}