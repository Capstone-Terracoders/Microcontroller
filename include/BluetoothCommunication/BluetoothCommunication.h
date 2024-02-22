#ifndef BLUETOOTHCOMMUNICATION_H
#define BLUETOOTHCOMMUNICATION_H
#include <ArduinoBLE.h>

class BluetoothCommunication
{
public: 
BluetoothCommunication();
BluetoothCommunication(const char *deviceName);
~BluetoothCommunication();
void addCharacteristic(const BLEStringCharacteristic characteristic);

BLEDevice controller;
bool connectionStatus();
private: 
const char *_deviceName = "Arduino";
const char *_serviceUUID = "19B10000-E8F2-537E-4F6C-D104768A1214";
const char *_characteristicUUID = "19B10001-E8F2-537E-4F6C-D104768A1214";
const char *_characteristicValue = "Hello World";

};
#endif