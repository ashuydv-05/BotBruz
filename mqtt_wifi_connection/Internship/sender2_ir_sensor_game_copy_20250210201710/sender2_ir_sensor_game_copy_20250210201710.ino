#include <WiFi.h>
#include <esp_now.h>

#define IR_SENSOR_PIN 18  // Change if needed

int count = 0;
bool lastState = LOW;

// Define receiver MAC address
uint8_t RECEIVER_MAC[] = {0xF8, 0xB3, 0xB7, 0x7A, 0xE9, 0x3C};

// Structure for sending data
typedef struct struct_message {
    int player_id;
    int count;
} struct_message;

struct_message sendData;

void sendDataESPNow() {
    esp_err_t result = esp_now_send(RECEIVER_MAC, (uint8_t *)&sendData, sizeof(sendData));
    if (result != ESP_OK) {
        Serial.println("Error sending data");
    }
}

// IR Sensor Interrupt Function
void IR_Sensor_ISR() {
    if (digitalRead(IR_SENSOR_PIN) == HIGH) {
        count++;
        sendData.count = count;
        sendDataESPNow();
        Serial.print("Player ");
        Serial.print(sendData.player_id);
        Serial.print(" Count: ");
        Serial.println(count);
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(IR_SENSOR_PIN, INPUT);

    // Initialize WiFi in station mode
    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, RECEIVER_MAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    // Assign Player ID (Change for each sender)
    sendData.player_id = 2;  // Change to 2 for Sender 2
    sendData.count = 0;

    // Attach Interrupt to IR Sensor
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), IR_Sensor_ISR, RISING);
}

void loop() {
    // Nothing to do here, ISR handles counting and sending
}
