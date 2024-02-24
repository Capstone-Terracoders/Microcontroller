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


void BluetoothCommunication::addCharacteristicToList(BLECharacteristic &characteristic){
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
  BLECharacteristic characteristic =  BLECharacteristic(uuid, permissions, value);
  
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
  Serial.println("YO setting up");
  BLE.setAdvertisedService(*service);
  Serial.println(service->uuid());
  if(characteristics.size() <1){
    Serial.println("ERROR ---- No BLE characteristics setup");
    return;
  }
  BLE.addService(*service);

  // // Start advertising
  BLE.advertise();
}

bool BluetoothCommunication::writeCharacteristic(BLECharacteristic &charateristic, const char *data){
  return (charateristic.writeValue(data) ? true : false);
}
bool BluetoothCommunication::writeCharacteristic(const char *uuid, const char *data){
  for (auto& charateristic : characteristics) {
    if (charateristic.uuid() == uuid){
      return (charateristic.writeValue(data) ? true : false);
    }
  }
  return false;
}
