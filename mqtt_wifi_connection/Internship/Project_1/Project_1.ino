#define button1 4  // Endstop switch connected to GPIO 4
#define button2 17 // Push button connected to GPIO 17
#define relayPin 33 // Relay connected to GPIO 33

void setup() {
    pinMode(button1, INPUT);  
    pinMode(button2, INPUT); 
    pinMode(relayPin, OUTPUT); 
    Serial.begin(115200);
    digitalWrite(relayPin, HIGH); 
    pinMode(2,OUTPUT);
}

void loop() {
    int switch1 = digitalRead(button1); 
    int switch2 = digitalRead(button2);  
    //digitalWrite(relayPin, LOW); 
    if (switch1 == LOW) {  
        Serial.println("GAME START! READY");
        delay(5000); 
        
        if (switch2 == HIGH) {  
            Serial.println("Player ready");
            delay(2000);  
            Serial.println("READY!");
            digitalWrite(relayPin, LOW); 
            digitalWrite(2,HIGH);
            
        } else {
            Serial.println("Button 2 not pressed");
        }
    } else {
        Serial.println("WAIT! until button is pressed");
    }
    delay(200);  // Debouncing delay to stabilize button readings
}
