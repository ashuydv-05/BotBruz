#include <Bluepad32.h>
#define IN1  5   // Motor 1 Control Pin
#define IN2  18  
#define IN3  19  // Motor 2 Control Pin
#define IN4  21 

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
    String movement = "";
    if (ctl->axisY() < -200) {
        movement = "Moving Forward";
        moveForward();
    } else if (ctl->axisY() > 200) {
        movement = "Moving Backward";
        moveReverse();
    } else if (ctl->axisX() < -200) {
        movement = "Moving Left";
    } else if (ctl->axisX() > 200) {
        movement = "Moving Right";
    } else if (ctl->brake() > 500) {
        movement = "Braking";
    }
    
    if (!movement.isEmpty()) {
        Serial.println(movement);
    }
    
    if (ctl->a()) Serial.println("Button A pressed");
    if (ctl->b()) Serial.println("Button B pressed");
    if (ctl->x()) Serial.println("Button X pressed");
    if (ctl->y()) Serial.println("Button Y pressed");
    if (ctl->l1()) Serial.println("L1 pressed");
    if (ctl->r1()) Serial.println("R1 pressed");
    if (ctl->l2()) Serial.println("L2 pressed");
    if (ctl->r2()) Serial.println("R2 pressed");
 /*   if (ctl->select()) Serial.println("Select pressed");
    if (ctl->start()) Serial.println("Start pressed");
}*/}

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
    //stopMotors();  // Stop motors initially
}

void loop() {
    if (BP32.update()) {
        processControllers();
    }
    delay(150);
}
// Function to move both motors forward
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

// Function to move one motor forward and the other reverse
void moveOneForwardOneReverse() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Function to move one motor reverse and the other forward
/*void moveOneReverseOneForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to stop both motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}*/

