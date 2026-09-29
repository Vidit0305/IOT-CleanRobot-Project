#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define OBSTACLE_DISTANCE 15
#define MOTOR_SPEED 190

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo sensorServo;

void setup() {
  sensorServo.attach(10);
  sensorServo.write(115);
  delay(1000);
}

void loop() {
  int distance = readDistance();

  if (distance <= OBSTACLE_DISTANCE) {
    stopRobot();
    delay(100);

    moveBackward();
    delay(300);

    stopRobot();
    delay(100);

    int rightDistance = lookRight();
    int leftDistance = lookLeft();

    if (rightDistance >= leftDistance) {
      turnRight();
    } else {
      turnLeft();
    }

    stopRobot();
  } else {
    moveForward();
  }

  delay(40);
}

int readDistance() {
  int distance = sonar.ping_cm();

  if (distance == 0) {
    distance = MAX_DISTANCE;
  }

  return distance;
}

int lookRight() {
  sensorServo.write(50);
  delay(500);

  int distance = readDistance();

  sensorServo.write(115);
  return distance;
}

int lookLeft() {
  sensorServo.write(170);
  delay(500);

  int distance = readDistance();

  sensorServo.write(115);
  return distance;
}

void moveForward() {
  motor1.setSpeed(MOTOR_SPEED);
  motor2.setSpeed(MOTOR_SPEED);
  motor3.setSpeed(MOTOR_SPEED);
  motor4.setSpeed(MOTOR_SPEED);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(MOTOR_SPEED);
  motor2.setSpeed(MOTOR_SPEED);
  motor3.setSpeed(MOTOR_SPEED);
  motor4.setSpeed(MOTOR_SPEED);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopRobot() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  delay(500);

  moveForward();
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  delay(500);

  moveForward();
}