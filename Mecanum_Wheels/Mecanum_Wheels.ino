#define ML_ENA 6
#define ML_IN1 7
#define ML_IN2 5
#define ML_IN3 4
#define ML_IN4 2
#define ML_ENB 3

#define MR_ENA 11
#define MR_IN1 13
#define MR_IN2 12
#define MR_IN3 A4
#define MR_IN4 8
#define MR_ENB 10

#define BTN_LEFT A1
#define BTN_RIGHT A0

#define SPEED_FRONT_LEFT 255
#define SPEED_REAR_LEFT 200
#define SPEED_FRONT_RIGHT 255
#define SPEED_REAR_RIGHT 200

#define ACT_ENA 9
#define ACT_IN1 A2
#define ACT_IN2 A3

#define BTN_ACT_DOWN A5
#define BTN_ACT_UP 0

#define ACT_SPEED 255

void setup() {
  pinMode(ML_IN1, OUTPUT); pinMode(ML_IN2, OUTPUT);
  pinMode(ML_IN3, OUTPUT); pinMode(ML_IN4, OUTPUT);
  pinMode(ML_ENA, OUTPUT); pinMode(ML_ENB, OUTPUT);

  pinMode(MR_IN1, OUTPUT); pinMode(MR_IN2, OUTPUT);
  pinMode(MR_IN3, OUTPUT); pinMode(MR_IN4, OUTPUT);
  pinMode(MR_ENA, OUTPUT); pinMode(MR_ENB, OUTPUT);

  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  pinMode(ACT_ENA, OUTPUT);
  pinMode(ACT_IN1, OUTPUT);
  pinMode(ACT_IN2, OUTPUT);
  pinMode(BTN_ACT_DOWN, INPUT_PULLUP);
  pinMode(BTN_ACT_UP, INPUT_PULLUP);

  stopMotors();
  actuatorStop();
}

void setSpeed() {
  analogWrite(ML_ENA, SPEED_FRONT_LEFT);
  analogWrite(ML_ENB, SPEED_REAR_LEFT);
  analogWrite(MR_ENA, SPEED_FRONT_RIGHT);
  analogWrite(MR_ENB, SPEED_REAR_RIGHT);
}

void driveLeft() {
  setSpeed();
  digitalWrite(ML_IN1, HIGH); digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH); digitalWrite(ML_IN4, LOW);
  digitalWrite(MR_IN1, LOW); digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, HIGH); digitalWrite(MR_IN4, LOW);
}

void driveRight() {
  setSpeed();
  digitalWrite(ML_IN1, LOW); digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW); digitalWrite(ML_IN4, HIGH);
  digitalWrite(MR_IN1, HIGH); digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW); digitalWrite(MR_IN4, HIGH);
}

void stopMotors() {
  analogWrite(ML_ENA, 0);
  analogWrite(ML_ENB, 0);
  analogWrite(MR_ENA, 0);
  analogWrite(MR_ENB, 0);
  digitalWrite(ML_IN1, LOW); digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW); digitalWrite(ML_IN4, LOW);
  digitalWrite(MR_IN1, LOW); digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW); digitalWrite(MR_IN4, LOW);
}

void actuatorDown() {
  analogWrite(ACT_ENA, ACT_SPEED);
  digitalWrite(ACT_IN1, LOW);
  digitalWrite(ACT_IN2, HIGH);
}

void actuatorUp() {
  analogWrite(ACT_ENA, ACT_SPEED);
  digitalWrite(ACT_IN1, HIGH);
  digitalWrite(ACT_IN2, LOW);
}

void actuatorStop() {
  analogWrite(ACT_ENA, 0);
  digitalWrite(ACT_IN1, LOW);
  digitalWrite(ACT_IN2, LOW);
}

String lastState = "";

void loop() {
  bool leftPressed = digitalRead(BTN_LEFT) == LOW;
  bool rightPressed = digitalRead(BTN_RIGHT) == LOW;

  if (leftPressed && !rightPressed) {
    driveLeft();
    lastState = "left";
  } else if (rightPressed && !leftPressed) {
    driveRight();
    lastState = "right";
  } else if (!leftPressed && !rightPressed && lastState != "stopped") {
    stopMotors();
    lastState = "stopped";
  }

  bool downPressed = digitalRead(BTN_ACT_DOWN) == LOW;
  bool upPressed = digitalRead(BTN_ACT_UP) == LOW;

  if (downPressed && !upPressed) {
    actuatorDown();
  } else if (upPressed && !downPressed) {
    actuatorUp();
  } else {
    actuatorStop();
  }

  delay(50);
}