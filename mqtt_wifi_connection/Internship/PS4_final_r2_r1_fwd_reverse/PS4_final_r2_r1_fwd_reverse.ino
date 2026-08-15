#include <Bluepad32.h>

#define IN1  5   // Motor 1 Control Pin (DRV8833 AIN1)
#define IN2  18  // Motor 1 Control Pin (DRV8833 AIN2)
#define IN3  19  // Motor 2 Control Pin (DRV8833 BIN1)
#define IN4  21  // Motor 2 Control Pin (DRV8833 BIN2)



ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void onConnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("Controller connected at index=%d\n", i);
            myControllers[i] = ctl;
            break;
        }
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            break;
        }
    }
}

void processGamepad(ControllerPtr ctl) {
  
    if (ctl->axisX() < -200) { // Move Left
        moveLeft();
        Serial.println("Moving Left");
    } else if (ctl->axisX() > 200) { // Move Right
        moveRight();
        Serial.println("Moving Right");
    } else {
        stopMotors();
    }
      
    if (ctl->a()) Serial.println("Button A pressed");
   
    if (ctl->l2()){ Serial.println("moving backward");stopMotors();  moveReverse();}
    if (ctl->r2()) {Serial.println("Moving forward"); stopMotors(); moveForward();}
 }
    

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            processGamepad(myController);
        }
    }
}

void setup() {
    Serial.begin(115200);
     BP32.setup(&onConnectedController, &onDisconnectedController);
    BP32.forgetBluetoothKeys();
    BP32.enableVirtualDevice(false);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
    stopMotors();  // Stop motors initially
}

void loop() {
    if (BP32.update()) {
        processControllers();
    }
    delay(150);
}



void moveLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}


void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to move both motors in reverse
void moveReverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
