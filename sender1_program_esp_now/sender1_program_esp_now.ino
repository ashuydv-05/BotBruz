#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMac[] =  {0x8C, 0x4F, 0x00, 0x27, 0xF6, 0x0C}; // Replace with Receiver MAC

typedef struct struct_message {
    char message[250];  // Increased size for user input messages
} struct_message;

struct_message msg;

void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
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

    esp_now_register_send_cb(OnSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverMac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    Serial.println("Type a message and press Enter to send:");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');  // Read user input
        input.trim();  // Remove any unwanted spaces or newlines

        if (input.length() > 0) {
            strcpy(msg.message, input.c_str());  // Copy input into message structure
            esp_err_t result = esp_now_send(receiverMac, (uint8_t *)&msg, sizeof(msg));

            Serial.print("Sent: ");
            Serial.println(input);
        }
    }
}
