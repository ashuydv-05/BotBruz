#define RELAY_PIN 33  // Define the relay control pin

void setup() {
    Serial.begin(115200);
    pinMode(RELAY_PIN, OUTPUT);
    
    Serial.println("ESP32 Relay Control");
}

void loop() {
    Serial.println("Relay off");
    digitalWrite(RELAY_PIN, HIGH); // Turn relay ON
    delay(2000); // Wait for 2 seconds

    Serial.println("Relay on");
    digitalWrite(RELAY_PIN, LOW); // Turn relay OFF
    delay(2000); // Wait for 2 seconds
}
