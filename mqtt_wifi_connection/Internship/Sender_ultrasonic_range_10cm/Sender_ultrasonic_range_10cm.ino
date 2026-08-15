#include <WiFi.h>
#include <esp_now.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define RELAY_PIN 33

uint8_t receiverMAC[] = {0xF8, 0xB3, 0xB7, 0x7A, 0xE9, 0x3C};  // Receiver's MAC Address

typedef struct {
  int distance;
  bool relayState;
} SensorData;

SensorData data;

void sendCallback(const uint8_t *macAddr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_send_cb(sendCallback);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  
  // Determine relay state
  bool relayState = (distance < 10);
  digitalWrite(RELAY_PIN, relayState ? LOW : HIGH);

  // Display in Serial Monitor
  Serial.print("Distance: "); Serial.print(distance); Serial.print(" cm | Relay: ");
  Serial.println(relayState ? "ON" : "OFF");

  // Send data only if distance is under 10 cm
  if (relayState) {
    data.distance = distance;
    data.relayState = relayState;
    esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
    Serial.println("Data Sent to Receiver!");
  }

  delay(1000);
}