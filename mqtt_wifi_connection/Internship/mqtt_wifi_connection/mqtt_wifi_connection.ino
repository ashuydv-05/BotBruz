#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Credentials
const char* ssid = "Roboarena";
const char* password = "Roboarena@7020";

// MQTT Broker Details (Localhost if running Mosquitto on the same PC)
const char* mqtt_server = "192.168.1.116";  // Change to your PC's local IP address
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/data";  // Topic to publish

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
    delay(10);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("Connected!");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Publish dummy data
    String payload = "Hello from ESP32!";
    client.publish(mqtt_topic, payload.c_str());

    Serial.println("Published: " + payload);
    delay(5000);  // Publish every 5 seconds
}
