const int irPin = 18;  // IR sensor connected to GPIO34 (ADC1)
int userInput;          // Variable to store user input
int detectionCount = 0; // Counter for object detections
bool lastState = HIGH;  // Store the previous state of IR sensor

void setup() {
    Serial.begin(115200);  // Initialize Serial Monitor
    pinMode(irPin, INPUT); // Set IR sensor as input
    Serial.println("Enter '4' to activate IR sensor:");
}

void loop() {
    // Wait for user input to activate IR sensor
    if (Serial.available() > 0) {
        userInput = Serial.parseInt();  // Read user input as integer

        if (userInput == 4) {  // If user enters 4, activate sensor
            Serial.println("IR Sensor Activated! Checking for objects...");

            while (true) { // Infinite loop to continuously check sensor
                bool currentState = digitalRead(irPin);  // Read IR sensor as HIGH or LOW

                // Detect HIGH → LOW transition (object appears)
                if (lastState == HIGH && currentState == LOW) {
                    detectionCount++; // Increment detection count
                    Serial.print("Object detected! Total detections: ");
                    Serial.println(detectionCount);
                }
                else{
                  Serial.println("Object not detected");
                }

                lastState = currentState; // Update last state
                delay(500); // Debounce delay to prevent false triggers
            }
        } else {
            Serial.println("Invalid input! Enter '4' to activate IR sensor.");
        }
    }
}