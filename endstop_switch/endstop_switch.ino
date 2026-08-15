#define button1 4  // Connect the signal pin to GPIO 4
#define button2 17
#define button3 33
void setup() {
    pinMode(button1, INPUT); 
    pinMode(button2,INPUT_PULLUP);
    pinMode(button3,OUTPUT);
    Serial.begin(115200);
}

void loop() {
    int switch1 = digitalRead(button1);
    int switch2= digitalRead(button2);
    if (switch1 == LOW) {  // Active when pressed
        Serial.println("GAME START! READY");
        delay(2000);
        if(switch2==LOW){
          Serial.println("PLayer ready");
          delay(500);
          Serial.println("READY!");
          digitalWrite(button3, HIGH); }
        else{ 
          Serial.println("Button 2 not pressed");

        }
        
      
    } else {
        Serial.println("WAIT! until button is pressed");
    }
    delay(500);
}
