#include "./DataProcessing/DataProcessing.h"
DataProcessing::DataProcessing() {}
DataProcessing::~DataProcessing() {}

DataProcessing::DataProcessing(float rakeSpeedTimeOut, float harvesterSpeedTimeOut) {
    _rakeSpeedTimeOut = rakeSpeedTimeOut;
    _harvesterSpeedTimeOut = harvesterSpeedTimeOut;
}

// Rake height
// parameters:
// rakeHeightData: The data from the rake_height sensor
// heightOfRake: The height of the rake in meters
// returns the height of the rake in meters
float DataProcessing::calculateRakeHeight(int rakeHeightData, float heightOfRake, int maxDataValue, int minDataValue) {
    // Adjust the data to the max and min values
    // These are bounds set for the sensor in case the sensor cannot complete the full range
    if (rakeHeightData > maxDataValue) {
        rakeHeightData = maxDataValue;
    } else if (rakeHeightData < minDataValue) {
        rakeHeightData = minDataValue;
    }
    // Shift rakeHeightData by the minDataValue
    float adjustedHeightRakeData = static_cast<float>(rakeHeightData)-static_cast<float>(minDataValue);
    // Shift the maxDataValue by the minDataValue
    float adjustedMaxDataValue = static_cast<float>(maxDataValue)-static_cast<float>(minDataValue);
    return heightOfRake * (adjustedHeightRakeData/adjustedMaxDataValue);
}
// Bush height
// bushHeightData: The data from the bush_height sensor
// calibrationFactor: The calibration factor for the sensor
// returns the height of the bush in meters
float DataProcessing::calculateBushHeight(int bushHeightData, float calibrationFactor) {
    return ((bushHeightData / PWM_TO_INCHES) * INCHES_TO_METERS * calibrationFactor);
}
// Rake Rotational Speed
// rakeRotationSpeedData: 1 if the rake has rotated once, 0 if the rake has not rotated
// divisionOfCircle: The number of divisions in the circle
// radiusOfRake: The radius of the rake meters
// returns the rotational speed of the rake in RPM
float DataProcessing::calculateRakeRotationalSpeed(int rakeRotationSpeedData, int divisionOfCircle,
float radiusOfRake) {
    int64_t current_time = millis();
    int64_t elapsed_time = current_time - _tprev_RakeRotationalSpeed;
    // Serial.println("Called");
    // If the _dt has not been set, set it to the current time
    if (_tprev_RakeRotationalSpeed <= 0) {
        _tprev_RakeRotationalSpeed = current_time;
        return _rakeRotationalSpeed;
    }
    // Check for the timeout
    if (_rakeSpeedTimeOut < (elapsed_time) / MILISECONDS_TO_SECONDS) {
        _rakeRotationalSpeed = 0;
    } else {
        // calculate Miliseconds per rotation
        _dt_RakeRotationalSpeed = elapsed_time;
        _tprev_RakeRotationalSpeed = current_time;
        // convert to minutes
        float minutes = static_cast<float>(_dt_RakeRotationalSpeed) / MILISECONDS_TO_MINUTES;
        _rakeRotationalSpeedSwitch = true;
        // calculate RMP of rake
        _rakeRotationalSpeed = ((rakeRotationSpeedData-_prevRakeRotationalSpeedData)/divisionOfCircle) / (minutes);
        _prevRakeRotationalSpeedData = rakeRotationSpeedData;
    }
    return _rakeRotationalSpeed;
}

// Linear speed of the harvester m/s
// harvesterLinearSpeedData: 1 if the harvester has rotated once, 0 if the harvester has not rotated
// divisionOfCircle: The number of divisions in the circle
// radiusOfHavesterWheel: The radius of the harvester wheel in meters
// returns the linear speed of the harvester in m/s
float DataProcessing::calculateHavesterLinearSpeed(int harvesterLinearSpeedData, int divisionOfCircle,
float radiusOfHavesterWheel) {
    int64_t current_time = millis();
    int64_t elapsed_time = current_time - _tprev_HarvesterLinearSpeed;
    // If the _dt has not been set, set it to the current time
    if (_tprev_HarvesterLinearSpeed <= 0) {
        _tprev_HarvesterLinearSpeed = current_time;
        return _harvesterLinearSpeed;
    }
        // Check for the timeout
    if (_harvesterSpeedTimeOut < (elapsed_time) / MILISECONDS_TO_SECONDS) {
        _harvesterLinearSpeed = 0;
    } else {
        // calculate Miliseconds per rotation
        _dt_HarvesterLinearSpeed = elapsed_time;
        _tprev_HarvesterLinearSpeed = current_time;
        // convert to seconds
        float seconds = static_cast<float>(_dt_HarvesterLinearSpeed) / MILISECONDS_TO_SECONDS;
        _harvesterLinearSpeedSwitch = true;
        // calculate Speed of harvester
        int numberOfRotations = harvesterLinearSpeedData - _prevHarvesterSpeedData;
        _harvesterLinearSpeed = (((2*radiusOfHavesterWheel*M_PI)*numberOfRotations)/divisionOfCircle) / seconds;
        _prevHarvesterSpeedData = harvesterLinearSpeedData;
    }

    // Rake has rotated once, calculate the rotational speed
    if (harvesterLinearSpeedData == 0 && !_harvesterLinearSpeedSwitch) {
        // calculate Miliseconds per rotation
        // int64_t current_time = millis();
        _dt_HarvesterLinearSpeed = elapsed_time;
        _tprev_HarvesterLinearSpeed = current_time;
        // convert to seconds
        float seconds = static_cast<float>(_dt_HarvesterLinearSpeed) / MILISECONDS_TO_SECONDS;
        _harvesterLinearSpeedSwitch = true;
        // calculate Speed of harvester
        _harvesterLinearSpeed = ((2*radiusOfHavesterWheel*M_PI)/divisionOfCircle) / seconds;
    } else if (harvesterLinearSpeedData == 1 && _harvesterLinearSpeedSwitch) {
        _harvesterLinearSpeedSwitch = false;
    } else if (_harvesterSpeedTimeOut < (elapsed_time) / MILISECONDS_TO_SECONDS) {
        _harvesterLinearSpeed = 0;
    }
    return _harvesterLinearSpeed;
}
// Returns rake speed Timeout
float DataProcessing::getRakeSpeedTimeout() {
    return _rakeSpeedTimeOut;
}
// Returns Harvester Speed Timeout
float DataProcessing::getHarvesterSpeedTimeout() {
    return _harvesterSpeedTimeOut;
}
// Set the rake speed Timeout
void DataProcessing::setRakeSpeedTimeout(float rakeSpeedTimeout) {
    _rakeSpeedTimeOut = rakeSpeedTimeout;
}
// Set the Harvester speed Timeout
void DataProcessing::setHarvesterSpeedTimeout(float harvesterSpeedTimout) {
    _harvesterSpeedTimeOut = harvesterSpeedTimout;
}
