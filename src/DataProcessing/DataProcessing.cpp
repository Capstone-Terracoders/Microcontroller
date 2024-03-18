#include "./DataProcessing/DataProcessing.h"
DataProcessing::DataProcessing() {}
DataProcessing::DataProcessing(float rakeSpeedTimeOut, float harvesterSpeedTimeOut) {
    _rakeSpeedTimeOut = rakeSpeedTimeOut;
    _harvesterSpeedTimeOut = harvesterSpeedTimeOut;
}

DataProcessing::~DataProcessing() {}
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
    float conversionFactor = 147.0;  // Conversion factor of PWM to inches
    float inchesToMeters = 0.0254;  // Conversion factor of inches to meters
    return ((bushHeightData / conversionFactor) * inchesToMeters * calibrationFactor);
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

    // If the _dt has not been set, set it to the current time
    if (_tprev_RakeRotationalSpeed <= 0) {
        _tprev_RakeRotationalSpeed = current_time;
        return _rakeRotationalSpeed;
    }
    // Rake has rotated once, calculate the rotational speed
    if (rakeRotationSpeedData == 0 && !_rakeRotationalSpeedSwitch) {
        // calculate Miliseconds per rotation
        _dt_RakeRotationalSpeed = elapsed_time;
        _tprev_RakeRotationalSpeed = current_time;
        // convert to minutes
        float minutes = static_cast<float>(_dt_RakeRotationalSpeed) / 60000.0;
        _rakeRotationalSpeedSwitch = true;
        // calculate RMP of rake
        _rakeRotationalSpeed = divisionOfCircle / (minutes);
    } else if (rakeRotationSpeedData == 1 && _rakeRotationalSpeedSwitch) {
        _rakeRotationalSpeedSwitch = false;
    } else if (_rakeSpeedTimeOut < (elapsed_time) / 1000.0) {
        _rakeRotationalSpeed = 0;
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
        _tprev_HarvesterLinearSpeed = millis();
        return _harvesterLinearSpeed;
    }
    // Rake has rotated once, calculate the rotational speed
    if (harvesterLinearSpeedData == 0 && !_harvesterLinearSpeedSwitch) {
        // calculate Miliseconds per rotation
        int64_t current_time = millis();
        _dt_HarvesterLinearSpeed = elapsed_time;
        _tprev_HarvesterLinearSpeed = current_time;
        // convert to minutes
        float seconds = static_cast<float>(_dt_HarvesterLinearSpeed) / 1000.0f;
        _harvesterLinearSpeedSwitch = true;
        // calculate Speed of harvester
        _harvesterLinearSpeed = ((2*radiusOfHavesterWheel*M_PI)/divisionOfCircle) / seconds;
    } else if (harvesterLinearSpeedData == 1 && _harvesterLinearSpeedSwitch) {
        _harvesterLinearSpeedSwitch = false;
    } else if (_harvesterSpeedTimeOut < (elapsed_time) / 1000.0) {
        _harvesterLinearSpeed = 0;
    }
    return _harvesterLinearSpeed;
}
