#define IN1  5   // Motor 1 Control Pin
#define IN2  18  
#define IN3  19  // Motor 2 Control Pin
#define IN4  21  

void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();  // Stop motors initially
  Serial.println("Enter a number (1-4) to control the motors:");
}

void loop() {
  if (Serial.available() > 0) {  // Check if input is available
    String input = Serial.readStringUntil('\n');  // Read full input line
    input.trim();  // Remove any unwanted characters (spaces, \n, \r)

    if (input == "1") {
      Serial.println("Case 1: Both motors moving forward");
      moveForward();
    } else if (input == "2") {
      Serial.println("Case 2: Both motors moving in reverse");
      moveReverse();
    } else if (input == "3") {
      Serial.println("Case 3: Motor 1 forward, Motor 2 reverse");
      moveOneForwardOneReverse();
    } else if (input == "4") {
      Serial.println("Case 4: Motor 1 reverse, Motor 2 forward");
      moveOneReverseOneForward();
    } else {
      Serial.println("Invalid input! Enter 1, 2, 3, or 4.");
      stopMotors();
    }
  }
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
void moveOneReverseOneForward() {
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
}
