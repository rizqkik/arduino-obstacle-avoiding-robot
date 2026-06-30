#include <Servo.h>
#include <NewPing.h>

// L298N motor driver control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

// Ultrasonic sensor pins
#define TRIG_PIN A1
#define ECHO_PIN A2

#define MAXIMUM_DISTANCE 50
#define OBSTACLE_DISTANCE 20

boolean goesForward = false;
int distance = 50;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servo_motor;

void setup() {
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(10);

  // Set servo to center position
  servo_motor.write(100);
  delay(2000);

  // Initial distance readings for stabilization
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;

  delay(50);

  if (distance <= OBSTACLE_DISTANCE) {
    moveStop();
    delay(300);

    moveBackward();
    delay(300);

    moveStop();
    delay(300);

    distanceRight = lookRight();
    delay(300);

    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }

  distance = readPing();
}

int lookRight() {
  servo_motor.write(50);
  delay(500);

  int distance = readPing();
  delay(100);

  servo_motor.write(100);
  return distance;
}

int lookLeft() {
  servo_motor.write(150);
  delay(500);

  int distance = readPing();
  delay(100);

  servo_motor.write(100);
  return distance;
}

int readPing() {
  delay(70);

  int cm = sonar.ping_cm();

  // If no object is detected, assume the path is clear
  if (cm == 0) {
    cm = MAXIMUM_DISTANCE;
  }

  return cm;
}

void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

void moveBackward() {
  goesForward = false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);

  delay(500);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnLeft() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
