#ifndef DATAINTERPRETATION_H
#define DATAINTERPRETATION_H
#include <math.h>
#include <Arduino.h>

class DataInterpretation
{
public:
    // Constructors
    DataInterpretation();
    // Destructor
    ~DataInterpretation();

    // Accessors
    float optimalRakeHeight(float rakeHeightData, float bushHeightData, float rakeRotationalSpeed, float harvesterSpeed);
    float optimalRakeRotationSpeed(float rakeHeightData, float bushHeightData, float rakeRotationalSpeed, float harvesterSpeed);
    float setOptimalRakeHeightCoefficient(float rakeHeightCoefficient);
    float setOptimalRakeRotationalSpeedCoefficient(float rakeRotationalSpeedCoefficient);
    float getOptimalRakeHeightCoefficient();
    float getOptimalRakeRotationalSpeedCoefficient();
private: 
    float _rakeHeightCoefficient = 1.0f;
    float _rakeRotationalSpeedCoefficient = 1.0f;
};
#endif