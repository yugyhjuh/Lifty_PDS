//L motor driver
#define ML_IN1 7
#define ML_IN2 5
#define ML_IN3 4
#define ML_IN4 2
#define ML_ENA 6
#define ML_ENB 3

//R motor driver
#define MR_ENA 11
#define MR_IN1 13
#define MR_IN2 12
#define MR_IN3 8
#define MR_IN4 1
#define MR_ENB 9

//buttons
#define BTN_LEFT  A1
#define BTN_RIGHT A0

//calibrate speed pls they're all diff
#define SPEED_FRONT_LEFT  200
#define SPEED_REAR_LEFT   200
#define SPEED_FRONT_RIGHT 200
#define SPEED_REAR_RIGHT  200

void setup() {
  pinMode(ML_IN1, OUTPUT); pinMode(ML_IN2, OUTPUT);
  pinMode(ML_IN3, OUTPUT); pinMode(ML_IN4, OUTPUT);
  pinMode(ML_ENA, OUTPUT); pinMode(ML_ENB, OUTPUT);

  pinMode(MR_IN1, OUTPUT); pinMode(MR_IN2, OUTPUT);
  pinMode(MR_IN3, OUTPUT); pinMode(MR_IN4, OUTPUT);
  pinMode(MR_ENA, OUTPUT); pinMode(MR_ENB, OUTPUT);

  pinMode(BTN_LEFT,  INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  stopMotors();
}

void setSpeed() {
  analogWrite(ML_ENA, SPEED_FRONT_LEFT);
  analogWrite(ML_ENB, SPEED_REAR_LEFT);
  analogWrite(MR_ENA, SPEED_FRONT_RIGHT);
  analogWrite(MR_ENB, SPEED_REAR_RIGHT);
}

//we flipped the motor's direction so calinbrate accordingly
void driveLeft() {
  setSpeed();
  digitalWrite(ML_IN1, HIGH); digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH); digitalWrite(ML_IN4, LOW);
  digitalWrite(MR_IN1, LOW); digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW); digitalWrite(MR_IN4, HIGH);
}

void driveRight() {
  setSpeed();
  digitalWrite(ML_IN1, LOW); digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW); digitalWrite(ML_IN4, HIGH);
  digitalWrite(MR_IN1, HIGH); digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH); digitalWrite(MR_IN4, LOW);
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

String lastState = "";

void loop() {
  bool leftPressed  = digitalRead(BTN_LEFT)  == LOW;
  bool rightPressed = digitalRead(BTN_RIGHT) == LOW;

  if (leftPressed && !rightPressed) {
    driveLeft();
    lastState = "right";

  } else if (rightPressed && !leftPressed) {
    driveRight();
    lastState = "left";

  } else if (!leftPressed && !rightPressed && lastState != "stopped") {
    stopMotors();
    lastState = "stopped";
  }

  delay(50);
}