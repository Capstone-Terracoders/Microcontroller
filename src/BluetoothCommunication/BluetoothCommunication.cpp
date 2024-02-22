#include "./BluetoothCommunication/BluetoothCommunication.h"

// Create a BLE service
// BLEService ledService("c6df3eec-08ff-4e92-bf96-d6dd251b4121"); 
// create service, a collection of characteristics, 
// BLEByteCharacteristic switchCharacteristic("5a4ed7f3-221d-47c3-991b-09cca7ea00db", BLERead | BLEWrite); 
// create characteristic, fetchable data unit, can be written to. Kinda like a bucket, put stuff there get stuff out. Is my understanding 
//can read or write to characteristic
//Byte arrays: You can send raw byte sequences for more complex data structures or custom protocols, allowing advanced data transfer.


void sendSensorData() {
  //
}

// BluetoothCommunication::BluetoothCommunication(){
//   BLE.begin();
//   if (!BLE.begin()) {
//     Serial.println("Starting BLE failed!");
//     while (1);
//   }
//   BLE.setLocalName("Wild Blueberry Sensor System"); //Advertizing name
//   BLE.addService(ledService);
//   // ledService.addCharacteristic(switchCharacteristic);

//   switchCharacteristic.setValue(0);
//   // Get and print the BLE address
//   String address = BLE.address();
//   Serial.print("r4 Bluetooth address: ");
//   Serial.println(address);
//   BLE.advertise();//send ble packets to local devices 
//   Serial.println("Bluetooth device active, connect...");
// }
bool BluetoothCommunication::connectionStatus() {
  //wait for central to connect
  return controller;
}