//
// Class: WildBlueberrySensorSystem
// Description: This class is used as a standard library for the WildBlueberrySensorSystem
// It incldues all needed header files for the WildBlueberrySensorSystem
//
#ifndef WildBlueberrySensorSystem_h
#define WildBlueberrySensorSystem_h

#include <map>
#include <memory>
#include <string>

#include "./Sensors/HallEffectSensor/HallEffectSensor_NJK5002C.h"
#include "./Sensors/Potentiometer/Potentiometer_Analog.h"
#include "./Sensors/UltrasonicSensor/UtlrasonicSensor_MB1010.h"
#include "./DataProcessing/DataProcessing.h"
#include "./BluetoothCommunication/BluetoothCommunication.h"

#include "./ReadSensorData/ReadSensorData.h"
#include "./DataInterpretation/DataInterpretation.h"

#endif
