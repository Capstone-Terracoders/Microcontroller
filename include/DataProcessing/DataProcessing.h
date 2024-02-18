//
// Class: ReadSensorData
// Description: This class is used to read the sensor data from the sensors
//
#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H
#include <math.h>
#include <Arduino.h>


class DataProcessing
{
public:
    // Constructors
    DataProcessing();
    // Destructor
    ~DataProcessing();

    // Accessors
    float calculateRakeHeight(int rakeHeightData, float heightOfRake, int maxDataValue, int minDataValue);
    float calculateBushHeight(int bushHeightData, float calibrationFactor);
    float calculateRakeRotationalSpeed(int rakeRotationSpeedData, int divisionOfCircle, int radiusOfRake);
    float calculateHavesterLinearSpeed(int harvesterLinearSpeedData, int radiusOfHavesterWheel, int timeOfRotation);
private: 
    // Variables
    float _rakeHeight = 0.0f;
    float _bushHeight = 0.0f;
    float _rakeRotationalSpeed = 0.0f;
    float _harvesterLinearSpeed = 0.0f;
    unsigned long int _tprev_RakeRotationalSpeed = 0.0f;
    unsigned long int _tprev_HarvesterLinearSpeed = 0.0f;
    unsigned long int _dt_RakeRotationalSpeed = 0.0f;
    unsigned long int _dt_HarvesterLinearSpeed = 0.0f;
    bool _rakeRotationalSpeedSwitch = false;
    bool _harvesterLinearSpeedSwitch = false;
};

#endif