#include <Bluepad32.h>

#define IN1  5   // Motor 1 Control Pin (PWM)
#define IN2  18  // Motor 1 Direction Pin
#define IN3  19  // Motor 2 Control Pin (PWM)
#define IN4  21  // Motor 2 Direction Pin
#define PWM_FREQ  5000
#define PWM_CHANNEL1  0
#define PWM_CHANNEL2  1
#define PWM_RESOLUTION  8

int speedValue = 0; // Initial Speed
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
    int axisY = ctl->axisY();
    int axisX = ctl->axisX();

    speedValue = map(abs(axisY), 0, 512, 0, 255);
    
    if (axisY < -50) {
        Serial.println("Moving Forward");
        moveForward(speedValue);
    } else if (axisY > 50) {
        Serial.println("Moving Backward");
        moveReverse(speedValue);
    } else if (axisX < -50) {
        Serial.println("Turning Left");
        turnLeft(speedValue);
    } else if (axisX > 50) {
        Serial.println("Turning Right");
        turnRight(speedValue);
    } else {
        stopMotors();
    }
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
    
    ledcSetup(PWM_CHANNEL1, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_CHANNEL2, PWM_FREQ, PWM_RESOLUTION);
    
    ledcAttachPin(IN1, PWM_CHANNEL1);
    ledcAttachPin(IN3, PWM_CHANNEL2);
    
    stopMotors();  // Stop motors initially
}

void loop() {
    if (BP32.update()) {
        processControllers();
    }
}

// Function to move both motors forward with PWM speed control
void moveForward(int speed) {
    digitalWrite(IN2, HIGH); // Set direction forward
    digitalWrite(IN4, HIGH);
    ledcWrite(PWM_CHANNEL1, speed);
    ledcWrite(PWM_CHANNEL2, speed);
}

// Function to move both motors in reverse with PWM speed control
void moveReverse(int speed) {
    digitalWrite(IN2, LOW); // Set direction backward
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL1, speed);
    ledcWrite(PWM_CHANNEL2, speed);
}

// Function to turn left while moving
void turnLeft(int speed) {
    digitalWrite(IN2, HIGH); // Set direction forward for one motor
    digitalWrite(IN4, LOW); // Reverse the other motor
    ledcWrite(PWM_CHANNEL1, speed / 2);
    ledcWrite(PWM_CHANNEL2, speed);
}

// Function to turn right while moving
void turnRight(int speed) {
    digitalWrite(IN2, LOW); // Reverse one motor
    digitalWrite(IN4, HIGH); // Forward the other motor
    ledcWrite(PWM_CHANNEL1, speed);
    ledcWrite(PWM_CHANNEL2, speed / 2);
}

// Function to stop both motors
void stopMotors() {
    ledcWrite(PWM_CHANNEL1, 0);
    ledcWrite(PWM_CHANNEL2, 0);
}
