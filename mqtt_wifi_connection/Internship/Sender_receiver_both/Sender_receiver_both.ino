#include <esp_now.h>
#include <WiFi.h>

uint8_t peer1[] = {0x8C, 0x4F, 0x00, 0x29, 0x73, 0x14};  // ESP32 #1 MAC
uint8_t peer2[] = {0x8C, 0x4F, 0x00, 0x27, 0xF6, 0x0C};  // ESP32 #2 MAC

typedef struct struct_message {
    char message[50];
} struct_message;

struct_message msg;

// 🔹 Callback function for sent message status
void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

// 🔹 Callback function for received messages
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    memcpy(&msg, incomingData, sizeof(msg));
    Serial.print("Received: ");
    Serial.println(msg.message);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_register_send_cb(OnSent);
    esp_now_register_recv_cb(OnDataRecv);

    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // 🔹 Add both ESPs as peers
    memcpy(peerInfo.peer_addr, peer1, 6);
    esp_now_add_peer(&peerInfo);

    memcpy(peerInfo.peer_addr, peer2, 6);
    esp_now_add_peer(&peerInfo);

    Serial.println("Type a message and press Enter to send:");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() > 0) {
            strcpy(msg.message, input.c_str());
            esp_now_send(peer1, (uint8_t *)&msg, sizeof(msg));
            esp_now_send(peer2, (uint8_t *)&msg, sizeof(msg));

            Serial.print("Sent: ");
            Serial.println(input);
        }
    }
}
