//
// Class: ReadSensorData
// Description: This class is used to read the sensor data from the sensors
//
#ifndef SRC_DATAPROCESSING_DATAPROCESSING_H_
#define SRC_DATAPROCESSING_DATAPROCESSING_H_
#include <math.h>
#include <Arduino.h>

class DataProcessing {
 public:
    // Constructors
    DataProcessing();
    DataProcessing(float rakeSpeedTimeOut, float harvesterSpeedTimeOut);
    // Destructor
    ~DataProcessing();
    // Accessors
    float calculateRakeHeight(int rakeHeightData, float heightOfRake, int maxDataValue, int minDataValue);
    float calculateBushHeight(int bushHeightData, float calibrationFactor);
    float calculateRakeRotationalSpeed(int rakeRotationSpeedData, int divisionOfCircle, float radiusOfRake);
    float calculateHavesterLinearSpeed(int harvesterLinearSpeedData, int divisionOfCircle,
    float radiusOfHarvesterWheel);
    float getRakeSpeedTimeout();
    float getHarvesterSpeedTimeout();
    // Mutators
    void setRakeSpeedTimeout(float rakeSpeedTimeout);
    void setHarvesterSpeedTimeout(float harvesterSpeedTimout);
    // Constants
    static constexpr float MILISECONDS_TO_MINUTES = 60000.0;
    static constexpr float MILISECONDS_TO_SECONDS = 1000.0;
    static constexpr float PWM_TO_INCHES = 147.0;
    static constexpr float INCHES_TO_METERS = 0.0254;

 private:
    // Variables
    float _rakeHeight = 0.0f;
    float _bushHeight = 0.0f;
    float _rakeRotationalSpeed = 0.0f;
    float _harvesterLinearSpeed = 0.0f;
    int64_t _tprev_RakeRotationalSpeed = 0.0f;
    int64_t _tprev_HarvesterLinearSpeed = 0.0f;
    int64_t _dt_RakeRotationalSpeed = 0.0f;
    int64_t _dt_HarvesterLinearSpeed = 0.0f;
    bool _rakeRotationalSpeedSwitch = false;
    bool _harvesterLinearSpeedSwitch = false;
    float _rakeSpeedTimeOut = 10.0f;  // Time out for the rake speed - seconds
    float _harvesterSpeedTimeOut = 10.0f;  // Time out for the harvester speed - seconds
    int _prevRakeRotationalSpeedData = 0;
    int _prevHarvesterSpeedData = 0;
};
#endif  // SRC_DATAPROCESSING_DATAPROCESSING_H_
