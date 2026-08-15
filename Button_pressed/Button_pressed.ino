// Define the button pin
#define BUTTON_PIN 12 // Change this according to your wiring

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor
    Serial.begin(115200); // Start serial communication
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN); // Read button state
    
    if (buttonState == LOW) { // Button is pressed (active low)
        Serial.println("Button Pressed");
    } else {
        Serial.println("Button Not Pressed");
    }
    
    delay(200); // Small delay to avoid excessive serial prints
}