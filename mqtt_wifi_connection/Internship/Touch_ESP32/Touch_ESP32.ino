// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop() {
  if(touchRead(4)<12)
  {
  Serial.print("Touch detected ");
  
  Serial.println(touchRead(4));  // get touch value on GPIO 4
  delay(100);}
  else
  {
    Serial.println("Touch not detected");
  }
  delay(1000);
}