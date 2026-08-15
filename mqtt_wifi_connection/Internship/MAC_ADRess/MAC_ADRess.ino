#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    delay(1000);  // Small delay to stabilize

    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {}
