#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>

// Firebase project credentials
#define API_KEY "AIzaSyAqMcghA5prRyxewoSG1wOmxH8trMGsAoc"
#define FIREBASE_PROJECT_ID "esp32-firebase-new"
#define DATABASE_URL "https://firestore.googleapis.com/v1/projects/esp32-firebase-new/databases/(default)/documents/"

// WiFi credentials
#define WIFI_SSID "Priti's A16"
#define WIFI_PASSWORD "Priti2024"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to WiFi");

    // Firebase configuration
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    Firebase.begin(&config, NULL);
    Firebase.reconnectWiFi(true);

    while (!Firebase.ready()) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nFirebase Initialized Successfully!");
}

void loop() {
    Serial.println("\nEnter Card Number:");
    while (Serial.available() == 0);  // Wait for user input

    String cardNumber = Serial.readStringUntil('\n');
    cardNumber.trim();  // Remove extra spaces

    if (cardNumber.length() > 0) {
        String documentPath = "Cards/" + cardNumber;

        Serial.print("Fetching data from: ");
        Serial.println(documentPath);

        // Get Firestore document
        if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "default", documentPath.c_str())) {
            Serial.println("Firestore Response:");
            Serial.println(fbdo.payload());  // Print the full response

            FirebaseJson json;
            json.setJsonData(fbdo.payload().c_str());

            FirebaseJsonData jsonData;
            if (json.get(jsonData, "fields/amount/integerValue") || json.get(jsonData, "fields/amount/doubleValue")) {
                int amount = jsonData.to<int>();
                Serial.print("Card Balance: ₹");
                Serial.println(amount);

                // Deduct ₹10 and update Firestore
                int newAmount = amount - 10;
                FirebaseJson updateJson;
                updateJson.set("fields/amount/integerValue", newAmount);

                if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "default", documentPath.c_str(), updateJson.raw(), "amount")) {
                    Serial.print("New Balance Updated: ₹");
                    Serial.println(newAmount);
                } else {
                    Serial.print("Failed to update balance: ");
                    Serial.println(fbdo.errorReason());
                }
            } else {
                Serial.println("Error: 'amount' field not found in document.");
            }
        } else {
            Serial.print("Error fetching document: ");
            Serial.println(fbdo.errorReason());
        }
    } else {
        Serial.println("Invalid input. Please enter a valid card number.");
    }

    delay(5000);
}
