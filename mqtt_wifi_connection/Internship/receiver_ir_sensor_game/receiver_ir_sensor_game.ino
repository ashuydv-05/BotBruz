#include <WiFi.h>
#include <esp_now.h>

#define RELAY_PIN 4  // Relay control pin

int player1_count = 0;
int player2_count = 0;

// Structure to receive data
typedef struct struct_message {
    int player_id;
    int count;
} struct_message;

struct_message receivedData;

// Callback function for receiving data (Updated function signature)
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
    memcpy(&receivedData, incomingData, sizeof(receivedData));

    if (receivedData.player_id == 1) {
        player1_count = receivedData.count;
    } else if (receivedData.player_id == 2) {
        player2_count = receivedData.count;
    }

    Serial.print("Player 1: ");
    Serial.print(player1_count);
    Serial.print(" | Player 2: ");
    Serial.println(player2_count);

    // Check for Winner
    if (player1_count >= 10) {
        Serial.println("Player 1 Wins!");
        digitalWrite(RELAY_PIN, HIGH);
        delay(5000);
        digitalWrite(RELAY_PIN, LOW);
        player1_count = 0;
        player2_count = 0;
    } else if (player2_count >= 10) {
        Serial.println("Player 2 Wins!");
        digitalWrite(RELAY_PIN, HIGH);
        delay(5000);
        digitalWrite(RELAY_PIN, LOW);
        player1_count = 0;
        player2_count = 0;
    }
}

void setup() {
    Serial.begin(115200);
    
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);  // Register the updated callback function
}

void loop() {
    // Nothing to do here, ESP-NOW callback handles everything
}
