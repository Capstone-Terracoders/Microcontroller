#ifndef SRC_DATAINTERPRETATION_DATAINTERPRETATION_H_
#define SRC_DATAINTERPRETATION_DATAINTERPRETATION_H_
#include <math.h>
#include <Arduino.h>

class DataInterpretation{
 public:
    // Constructors
    DataInterpretation();
    // Destructor
    ~DataInterpretation();
    // Accessors
    float optimalRakeHeight(float heightOfPlant, float lenghtOfRakeTeeth,
    float angleOfInclinationOfRake, float radiusOfReel, float angularSpeedOfReel);
    float optimalRakeRotationSpeed(float rakeHeightData, float bushHeightData,
    float rakeRotationalSpeed, float harvesterSpeed);
    float setOptimalRakeHeightCoefficient(float rakeHeightCoefficient);
    float setOptimalRakeRotationalSpeedCoefficient(float rakeRotationalSpeedCoefficient);
    float getOptimalRakeHeightCoefficient();
    float getOptimalRakeRotationalSpeedCoefficient();
 private:
    float _rakeHeightCoefficient = 1.0f;
    float _rakeRotationalSpeedCoefficient = 1.0f;
};
#endif  // SRC_DATAINTERPRETATION_DATAINTERPRETATION_H_
