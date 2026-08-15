#include <esp_now.h>
#include <WiFi.h>

#define RELAY_PIN 33  // GPIO2 controls the relay

// Structure to receive data
typedef struct {
    int count;
} DataPacket;

DataPacket sender1Data, sender2Data;

int sender1Count = 0;
int sender2Count = 0;

uint8_t sender1MAC[] = {0x8C, 0x4F, 0x00, 0x27, 0xF6, 0x0C};  
uint8_t sender2MAC[] = {0x94, 0x54, 0xC5, 0xA9, 0x86, 0x94};

// Callback function when data is received
void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    if (memcmp(info->src_addr, sender1MAC, 6) == 0) {
        memcpy(&sender1Data, incomingData, sizeof(sender1Data));
        sender1Count = sender1Data.count;
        Serial.print("Sender 1 Count: ");
        Serial.println(sender1Count);
    } 
    else if (memcmp(info->src_addr, sender2MAC, 6) == 0) {
        memcpy(&sender2Data, incomingData, sizeof(sender2Data));
        sender2Count = sender2Data.count;
        Serial.print("Sender 2 Count: ");
        Serial.println(sender2Count);
    }

    // Check for a winner
    if (sender1Count >= 10) {
        Serial.println("Sender 1 Wins! Relay ON for 5 seconds.");
        digitalWrite(RELAY_PIN, HIGH);
        delay(5000);
        digitalWrite(RELAY_PIN, LOW);
        sender1Count = 0;
        sender2Count = 0;
    } 
    else if (sender2Count >= 10) {
        Serial.println("Sender 2 Wins! Relay ON for 5 seconds.");
        digitalWrite(RELAY_PIN, LOW);
        delay(5000);
        digitalWrite(RELAY_PIN, HIGH);
        sender1Count = 0;
        sender2Count = 0;
    }
}

void setup() {
    Serial.begin(115200);
    
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Initially off

    WiFi.mode(WIFI_STA);
    
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    // Register receive callback (using new function prototype)
    esp_now_register_recv_cb(onReceive);
}

void loop() {
    // Nothing to do here, everything runs in the callback
}
