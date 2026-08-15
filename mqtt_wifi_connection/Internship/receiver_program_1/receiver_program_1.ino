#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    char message[50];  // Match the size in the sender
} struct_message;

struct_message receivedMsg;

// 🔹 Corrected function signature
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    memcpy(&receivedMsg, incomingData, sizeof(receivedMsg));
    Serial.print("Received: ");
    Serial.println(receivedMsg.message);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    // 🔹 Corrected function call
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    // No need to do anything in the loop
}
