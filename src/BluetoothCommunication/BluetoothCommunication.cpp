#include "./BluetoothCommunication/BluetoothCommunication.h"

BluetoothCommunication::BluetoothCommunication(){
}

BluetoothCommunication::BluetoothCommunication(const char *deviceName, BLEService *serviceUUID){
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
  _deviceName = deviceName;
  service =  serviceUUID;
}

BluetoothCommunication::~BluetoothCommunication(){
}


void BluetoothCommunication::addCharacteristicToList(BLEStringCharacteristic &characteristic){
  characteristics.push_back(characteristic);
  if (*service) {
        service->addCharacteristic(characteristic);
    } else {
        // Handle the case where 'service' is not properly initialized
        // Log an error or take appropriate action
        Serial.println("ERROR -- adding characteristic failed");
    }
}

void BluetoothCommunication::addCharacteristicToList(const char* uuid, uint16_t permissions, int value){
  BLEStringCharacteristic characteristic =  BLEStringCharacteristic(uuid, permissions, value);
  
  characteristics.push_back(characteristic);
  if (service) {
        service->addCharacteristic(characteristic);
    } else {
        // Handle the case where 'service' is not properly initialized
        // Log an error or take appropriate action
        Serial.println("ERROR -- adding characteristic failed");
    }
}
void BluetoothCommunication::begin(){
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
  
  // // set local name
  BLE.setLocalName(_deviceName);
  Serial.println("Setting up BLE...");
  BLE.setAdvertisedService(*service);
  Serial.println(service->uuid());
  if(characteristics.size() <1){
    Serial.println("ERROR ---- No BLE characteristics setup");
    return;
  }
  BLE.addService(*service);

  // // Start advertising
  BLE.advertise();
  Serial.println("BLE device advertising...");

}

bool BluetoothCommunication::writeCharacteristic(BLEStringCharacteristic &characteristic, const char *data){
  return (characteristic.writeValue(data) ? true : false);
}
bool BluetoothCommunication::writeCharacteristic(const char *uuid, const char *data){
  for (auto& characteristic : characteristics) {
    if (characteristic.uuid() == uuid){
      return (characteristic.writeValue(data) ? true : false);
    }
  }
  return false;
}

String BluetoothCommunication::receivedDataCharacteristic(const char *uuid, char *buffer, int length){
  
  for (auto& characteristic : characteristics) {
    if (characteristic.uuid() == uuid){
      if (characteristic.written()) {
        // Read the data
        characteristic.readValue(buffer,length);
        Serial.print("Received value: ");
        Serial.println(buffer);
        return buffer;
      }
      break;
    }
  }
  return "";
}