#include <WiFi.h>
#include <esp_now.h>

typedef struct {
  int distance;
  bool relayState;
} SensorData;

void receiveCallback(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  SensorData data;
  memcpy(&data, incomingData, sizeof(data));

  Serial.print("Received from: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }

  Serial.print(" | Distance = ");
  Serial.print(data.distance);
  Serial.println(" cm | Relay: ON");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_recv_cb(receiveCallback);
}

void loop() {
  // Nothing to do here, data is received in the callback
}