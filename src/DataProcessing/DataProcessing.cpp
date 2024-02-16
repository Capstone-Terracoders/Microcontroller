#include "./DataProcessing/DataProcessing.h"
DataProcessing::DataProcessing() {}

DataProcessing::~DataProcessing() {}
// Rake height
// parameters:
// rakeHeightData: The data from the rake_height sensor
// heightOfRake: The height of the rake in meters
// returns the height of the rake in meters
float DataProcessing::calculateRakeHeight(int rakeHeightData, int heightOfRake) {
    return heightOfRake / rakeHeightData;
}

float DataProcessing::calculateBushHeight(int bushHeightData) {
    return bushHeightData;
}
// Rake Rotational Speed
// rakeRotationSpeedData: 1 if the rake has rotated once, 0 if the rake has not rotated
// divisionOfCircle: The number of divisions in the circle
// radiusOfRake: The radius of the rake meters
// returns the rotational speed of the rake in RPM
float DataProcessing::calculateRakeRotationalSpeed(int rakeRotationSpeedData, int divisionOfCircle, int radiusOfRake) {
    // Serial.println("Calculating RPM");
    // Serial.println(_dt_RakeRotationalSpeed);
    // Serial.println(_rakeRotationalSpeedSwitch);
    // If the _dt has not been set, set it to the current time
    if (_tprev_RakeRotationalSpeed <= 0) {
        _tprev_RakeRotationalSpeed = millis();
        return _rakeRotationalSpeed;
    }
    // Rake has rotated once, calculate the rotational speed
    if (rakeRotationSpeedData == 0 && !_rakeRotationalSpeedSwitch) {
        // calculate Miliseconds per rotation
        unsigned long int current_time = millis();
        _dt_RakeRotationalSpeed = current_time - _tprev_RakeRotationalSpeed;
        _tprev_RakeRotationalSpeed = current_time;
        // convert to minutes 
        float minutes = float(_dt_RakeRotationalSpeed) / 60000.0;
        _rakeRotationalSpeedSwitch = true;
        // calculate RMP of rake
        _rakeRotationalSpeed = divisionOfCircle / (minutes);
    }
    else if (rakeRotationSpeedData == 1 && _rakeRotationalSpeedSwitch) {
        _rakeRotationalSpeedSwitch = false;
    }
    return _rakeRotationalSpeed;
}


// Linear speed of the harvester m/s
// harvesterLinearSpeedData: 1 if the harvester has rotated once, 0 if the harvester has not rotated
// divisionOfCircle: The number of divisions in the circle
// radiusOfHavesterWheel: The radius of the harvester wheel in meters
// returns the linear speed of the harvester in m/s
float DataProcessing::calculateHavesterLinearSpeed(int harvesterLinearSpeedData, int divisionOfCircle, int radiusOfHavesterWheel) {
    // If the _dt has not been set, set it to the current time
    if (_tprev_HarvesterLinearSpeed <= 0) {
        _tprev_HarvesterLinearSpeed = millis();
        return _harvesterLinearSpeed;
    }
    // Rake has rotated once, calculate the rotational speed
    if (harvesterLinearSpeedData == 0 && !_harvesterLinearSpeedSwitch) {
        // calculate Miliseconds per rotation
        unsigned long int current_time = millis();
        _dt_HarvesterLinearSpeed = current_time - _tprev_HarvesterLinearSpeed;
        _tprev_HarvesterLinearSpeed = current_time;
        // convert to minutes 
        float seconds = float(_dt_HarvesterLinearSpeed) / 1000.0;
        _harvesterLinearSpeedSwitch = true;
        // calculate Speed of harvester
        _harvesterLinearSpeed = ((2*radiusOfHavesterWheel*M_PI)/divisionOfCircle) / seconds;
    }
    else if (harvesterLinearSpeedData == 1 && _harvesterLinearSpeedSwitch) {
        _harvesterLinearSpeedSwitch = false;
    }
    return _harvesterLinearSpeed;
}