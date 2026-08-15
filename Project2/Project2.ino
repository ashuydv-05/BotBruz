#define SWITCH1_PIN  5  // First endstop switch pin
#define SWITCH2_PIN  18 // Second endstop switch pin
#define RELAY_PIN    33 // Relay control pin

int count = 0;
bool gameRunning = false;
bool relayState = false;

void setup() {
    pinMode(SWITCH1_PIN, INPUT_PULLUP);
    pinMode(SWITCH2_PIN, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    Serial.begin(115200);
}

void toggleRelay() {
    if (digitalRead(SWITCH2_PIN) == LOW) {
        while (digitalRead(SWITCH2_PIN) == LOW) {
            delay(100);
        }
        count++;
        Serial.print("Switch 2 pressed: ");
        Serial.println(count);
    }

    if (count == 5) {
        relayState = !relayState;
        digitalWrite(RELAY_PIN, relayState ? LOW : HIGH);
        Serial.println(relayState ? "Relay ON. Game running..." : "Relay OFF. Game stopped.");
        count = 0;
    }
}

void loop() {
    if (!gameRunning && digitalRead(SWITCH1_PIN) == LOW) {
        Serial.println("Switch 1 pressed. Enter the pin number to start the game:");
        while (!Serial.available());
        int userInput = Serial.parseInt();

        if (userInput == SWITCH1_PIN) {
            Serial.println("Correct input! Game started.");
            gameRunning = true;
            count = 0;
        } else {
            Serial.println("Wrong input! Try again.");
        }
    }

    if (gameRunning) {
        toggleRelay();
    }
}
