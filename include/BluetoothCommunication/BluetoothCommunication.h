#ifndef BLUETOOTHCOMMUNICATION_H
#define BLUETOOTHCOMMUNICATION_H
#include <ArduinoBLE.h>
#include <vector>

class BluetoothCommunication
{
public: 
BluetoothCommunication();
BluetoothCommunication(const char *deviceName, BLEService *serviceUUID);
~BluetoothCommunication();

void addCharacteristicToList(BLECharacteristic &characteristic);
void addCharacteristicToList(const char* uuid, uint16_t permissions, int value);
void begin();

bool writeCharacteristic(BLECharacteristic &charateristic, const char *data);
bool writeCharacteristic(const char *uuid, const char *data);

BLEService *service;
std::vector<BLECharacteristic> characteristics;
private: 
const char *_deviceName = "Arduino";
};
#endif