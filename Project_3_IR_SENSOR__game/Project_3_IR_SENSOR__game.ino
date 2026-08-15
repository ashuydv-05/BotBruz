const int irPin1 = 18;  // First IR sensor connected to GPIO18
const int irPin2 = 19;  // Second IR sensor connected to GPIO19

int userInput;           // Variable to store user input
int detectionCount1 = 0; // Counter for IR sensor 1 detections
int detectionCount2 = 0; // Counter for IR sensor 2 detections

bool lastState1;  // Store previous state of IR sensor 1
bool lastState2;  // Store previous state of IR sensor 2
bool gameRunning = false; // Flag to check if game is running
bool gameEnded = false;   // Flag to ensure winner is printed only once

void setup() {
    Serial.begin(115200);  // Initialize Serial Monitor
    pinMode(irPin1, INPUT); // Set IR sensor 1 as input
    pinMode(irPin2, INPUT); // Set IR sensor 2 as input
    Serial.println("Enter '4' to start the game.");

    // Read initial state of IR sensors to prevent false initial count
    lastState1 = digitalRead(irPin1);
    lastState2 = digitalRead(irPin2);
}

void loop() {
    // Wait for user input to start the game
    if (!gameRunning && Serial.available() > 0) {
        userInput = Serial.parseInt();  // Read user input

        if (userInput == 4) {  
            Serial.println("Game Started! First to reach 5 detections wins!");
            gameRunning = true;  // Enable IR sensor monitoring

            // Reinitialize sensor state to avoid false first counts
            lastState1 = digitalRead(irPin1);
            lastState2 = digitalRead(irPin2);
            detectionCount1 = 0;
            detectionCount2 = 0;
            gameEnded = false;
        } else {
            Serial.println("Invalid input! Enter '4' to start the game.");
        }
    }

    // If game is running and hasn't ended, check sensor detections
    if (gameRunning && !gameEnded) {
        bool currentState1 = digitalRead(irPin1);  // Read IR sensor 1 state
        bool currentState2 = digitalRead(irPin2);  // Read IR sensor 2 state

        // Detect HIGH → LOW transition (object detected) for sensor 1
        if (lastState1 == HIGH && currentState1 == LOW) {
            detectionCount1++;
            Serial.print("IR Sensor 1 detected object! Total: ");
            Serial.println(detectionCount1);
        }

        // Detect HIGH → LOW transition (object detected) for sensor 2
        if (lastState2 == HIGH && currentState2 == LOW) {
            detectionCount2++;
            Serial.print("IR Sensor 2 detected object! Total: ");
            Serial.println(detectionCount2);
        }

        // Check if any sensor reaches 5 detections first
        if (detectionCount1 == 5) {
            Serial.println("🎉 Player 1 Wins! 🎉");
            gameEnded = true; // Stop further detection
        } 
        else if (detectionCount2 == 5) {
            Serial.println("🎉 Player 2 Wins! 🎉");
            gameEnded = true; // Stop further detection
        }

        // Update last states
        lastState1 = currentState1;
        lastState2 = currentState2;

        delay(200); // Shorter debounce delay for smoother response
    }
}
