#include <esp_now.h>
#include <WiFi.h>

#define IR_SENSOR_PIN 4  // Connect the IR sensor to GPIO4

// Structure to send data
typedef struct {
    int count;
} DataPacket;

DataPacket data;
int count = 0;
bool lastState = LOW;

// Replace with the receiver's MAC address
uint8_t receiverMAC[] = {0x8C, 0x4F, 0x00, 0x29, 0x73, 0x14};

// Callback function when data is sent
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
    Serial.begin(115200);

    // Set ESP32 as Wi-Fi station
    WiFi.mode(WIFI_STA);
    
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    // Register send callback
    esp_now_register_send_cb(onSent);
    
    pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {
    bool currentState = digitalRead(IR_SENSOR_PIN);
    
    // Detect motion change (HIGH to LOW)
    if (currentState == HIGH && lastState == LOW) {
        count++;
        Serial.print("Finger motion detected! Count: ");
        Serial.println(count);

        // Send data to receiver
        data.count = count;
        esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
    }
    
    lastState = currentState; // Update last state
    delay(50); // Debounce delay
}
