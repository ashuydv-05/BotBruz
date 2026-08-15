#include <Arduino.h>
#include <WiFi.h>
const char* ssid= "Redmi";
const char* pass="Ashu2004";
void setupWifi(){
  delay(100);
  Serial.print("\nConnecting to");
  Serial.println(ssid);
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConnected to");
  Serial.println(ssid);
}
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   setupWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
