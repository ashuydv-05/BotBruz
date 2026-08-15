const int irPin = 34; // Use GPIO34 as the analog input pin

void setup() {
    Serial.begin(115200); // Higher baud rate for ESP32
    pinMode(12,INPUT_PULLUP);
}

void loop() {
    int sensorValue = analogRead(irPin);
    int push=digitalRead(12);
   // Read analog value from IR sensor
    //Serial.print("IR Sensor Value: ");
   // Serial.println(sensorValue); // Print the value to Serial Monitor
    if(push==LOW)
    {
      Serial.println("Button is pressed");
      
      if (sensorValue<2000) {  // Adjust threshold based on testing
      Serial.println("Object detected!");
      } 
      else {
        Serial.println("No object detected.");
       }
    //else
    //{
     // Serial.println("Button not pressed");
    //}
    delay(200);
    } }
    // Object detection logic (adjust threshold as per your sensor)
    // if (sensorValue < 2000) {  // Adjust threshold based on testing
    //     Serial.println("Object detected!");
    // } else {
    //     Serial.println("No object detected.");
    // }

    