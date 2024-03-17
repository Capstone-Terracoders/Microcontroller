#include "DataInterpretation/DataInterpretation.h"

DataInterpretation::DataInterpretation() {
}

DataInterpretation::~DataInterpretation() {
}

float DataInterpretation::optimalRakeHeight(float heightOfPlant, float lenghtOfRakeTeeth,
float angleOfInclinationOfRake, float radiusOfReel, float angularSpeedOfReel) {
    // Calculate the optimal rake height
    // Placeholder equation until the actual equation is known
    float optimalRakeHeight = heightOfPlant + lenghtOfRakeTeeth * cos(angleOfInclinationOfRake)
    + radiusOfReel*sin(angularSpeedOfReel);
    return optimalRakeHeight;
}

float DataInterpretation::optimalRakeRotationSpeed(float rakeHeightData, float bushHeightData,
float rakeRotationalSpeed, float harvesterSpeed) {
    // Calculate the optimal rake rotational speed
    // Placeholder equation until the actual equation is known
    float optimalRakeRotationSpeed = (rakeHeightData - bushHeightData) * (harvesterSpeed / rakeRotationalSpeed);
    return optimalRakeRotationSpeed;
}

float DataInterpretation::setOptimalRakeHeightCoefficient(float rakeHeightCoefficient) {
    _rakeHeightCoefficient = rakeHeightCoefficient;
    return _rakeHeightCoefficient;
}

float DataInterpretation::setOptimalRakeRotationalSpeedCoefficient(float rakeRotationalSpeedCoefficient) {
    _rakeRotationalSpeedCoefficient = rakeRotationalSpeedCoefficient;
    return _rakeRotationalSpeedCoefficient;
}

float DataInterpretation::getOptimalRakeHeightCoefficient() {
    return _rakeHeightCoefficient;
}

float DataInterpretation::getOptimalRakeRotationalSpeedCoefficient() {
    return _rakeRotationalSpeedCoefficient;
}
