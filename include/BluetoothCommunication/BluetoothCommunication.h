#ifndef INCLUDE_BLUETOOTHCOMMUNICATION_BLUETOOTHCOMMUNICATION_H_
#define INCLUDE_BLUETOOTHCOMMUNICATION_BLUETOOTHCOMMUNICATION_H_
#include <ArduinoBLE.h>
#include <vector>

class BluetoothCommunication{
 public:
    BluetoothCommunication();
    BluetoothCommunication(const char *deviceName, BLEService *serviceUUID);
    ~BluetoothCommunication();

    void addCharacteristicToList(const char* uuid, uint16_t permissions, int value);
    void begin();

    bool writeCharacteristic(const char *uuid, const char *data);
    String receivedDataCharacteristic(const char *uuid, char *buffer, int length);

    BLEService *service;
    BLEDevice *central;
    std::vector<BLEStringCharacteristic> characteristics;
 private:
    const char *_deviceName = "Arduino";
};
#endif  // INCLUDE_BLUETOOTHCOMMUNICATION_BLUETOOTHCOMMUNICATION_H_
