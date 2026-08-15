#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT"); 
    Serial.println("🔍 Scanning for Bluetooth devices...");
}

void loop() {
    SerialBT.discoverAsync([](BTAdvertisedDevice* device) {
        Serial.printf("📡 Found Device: %s - %s\n", device->getAddress().toString().c_str(), device->getName().c_str());
    });
    delay(5000);
}
