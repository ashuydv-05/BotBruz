#include <WiFi.h>
#include <esp_now.h>

#define IR_SENSOR_PIN 5  // Change if needed

int count = 0;
volatile bool motionDetected = false; // Flag to indicate motion detected

// Define receiver MAC address
uint8_t RECEIVER_MAC[] = {0xF8, 0xB3, 0xB7, 0x7A, 0xE9, 0x3C};

// Structure for sending data
typedef struct struct_message {
    int player_id;
    int count;
} struct_message;

struct_message sendData;

// Function to send data via ESP-NOW
void sendDataESPNow() {
    esp_err_t result = esp_now_send(RECEIVER_MAC, (uint8_t *)&sendData, sizeof(sendData));
    if (result != ESP_OK) {
        Serial.println("Error sending data");
    }
}

// IR Sensor Interrupt Function (only sets flag)
void IR_Sensor_ISR() {
    motionDetected = true;
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
    memset(&peerInfo, 0, sizeof(peerInfo));  // Clear structure
    memcpy(peerInfo.peer_addr, RECEIVER_MAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    // Assign Player ID (Change for each sender)
    sendData.player_id = 1;  // Change to 2 for Sender 2
    sendData.count = 0;

    // Attach Interrupt to IR Sensor
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), IR_Sensor_ISR, RISING);
}

void loop() {
    if (motionDetected) {
        motionDetected = false; // Reset flag
        count++;
        sendData.count = count;
        sendDataESPNow();
        
        Serial.print("Player ");
        Serial.print(sendData.player_id);
        Serial.print(" Count: ");
        Serial.println(count);
    }
}
