#include <WiFi.h>
#include <FirebaseESP32.h>

// WiFi Credentials
#define WIFI_SSID "Priti's A16"
#define WIFI_PASSWORD "Priti2024"

// Firebase Credentials (✅ FIXED)
#define FIREBASE_HOST "https://esp32-firebase-15563-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "LsUyWOXNm5PjPMPMXoh4QtN2PO"

// Firebase and WiFi Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n🚀 ESP32 Starting...");

    // Connect to WiFi
    Serial.print("🔄 Connecting to WiFi: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
        attempts++;
        if (attempts > 20) {  // Timeout after 10 seconds
            Serial.println("\n❌ WiFi Connection Failed! Check SSID & Password.");
            return;
        }
    }
    Serial.println("\n✅ WiFi Connected!");
    Serial.print("📶 IP Address: ");
    Serial.println(WiFi.localIP());

    // Initialize Firebase
    Serial.println("🔥 Connecting to Firebase...");
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("✅ Firebase Connected!");
    Serial.println("📌 Enter data in Serial Monitor to send to Firebase:");
}

void loop() {
    if (Serial.available() > 0) {
        String inputData = Serial.readStringUntil('\n');  // Read input from Serial Monitor
        inputData.trim();  // Remove extra spaces

        Serial.print("🔼 Sending data to Firebase: ");
        Serial.println(inputData);

        if (Firebase.setString(fbdo, "/ESP32/InputData", inputData)) {
            Serial.println("✅ Data uploaded successfully!");
        } else {
            Serial.print("❌ Upload failed! Error: ");
            Serial.println(fbdo.errorReason());
        }
    }
}
