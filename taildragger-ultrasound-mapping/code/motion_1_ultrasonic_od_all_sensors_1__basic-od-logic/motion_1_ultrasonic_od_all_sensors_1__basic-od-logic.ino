
/*
 * Noob Robotics: Taildragging Ultrasonic Sensor Testing Platform
 * Basic code for motion/obstacle detection using 4 HC-SR04 ultrasonic sensors
 * 
 * The robot dimensions for this code are roughly 12" by 12" although the robot
 * is more of a rectangular shape along the long axis(towards forward motion).
 */

#include <Servo.h>

// drive servos
Servo servoLeft;
Servo servoRight;
int seLeFoPos = 85;
int seRiFoPos = 96;
int seLeBaPos = 95;
int seRiBaPos = 84;
int seLeStPos = 90;
int seRiStPos = 90;

// ultrasonic sensors
int usSensorTrigPinFrontCenter = 11; // added last
int usSensorTrigPinFrontLeft = 2;
int usSensorTrigPinFrontRight = 3;
int usSensorTrigPinBackLeft = 4;
int usSensorTrigPinBackRight = 5;
int usSensorEchoPinFrontCenter = 10;
int usSensorEchoPinFrontLeft = 6;
int usSensorEchoPinFrontRight =7;
int usSensorEchoPinBackLeft = 8;
int usSensorEchoPinBackRight = 9;

// ultrasonic data variables
long durationFrontCenter;
long durationFrontLeft;
long durationFrontRight;
long durationBackLeft;
long durationBackRight;
int distanceFrontCenter;
int distanceFrontLeft;
int distanceFrontRight;
int distanceBackLeft;
int distanceBackRight;
int obstcaleThresholdForwardCenter = 16; // inches
int obstacleThresholdForward = 12;
int obstacleThresholdBackward = 6;
boolean obstacleDetected = false; // this is a general interrupt
boolean obstacleDetectedFrontCenter = false;
boolean obstacleDetectedFrontLeft = false;
boolean obstacleDetectedFrontRight = false;
boolean obstacleDetectedBackLeft = false;
boolean obstacleDetectedBackRight = false;

void setup() {
  // drive servos setup
  servoLeft.attach(12);
  servoRight.attach(13);

  // ultrasonic sensor setup
  pinMode(usSensorTrigPinFrontCenter, OUTPUT);
  pinMode(usSensorTrigPinFrontLeft, OUTPUT);
  pinMode(usSensorTrigPinFrontRight, OUTPUT);
  pinMode(usSensorTrigPinBackLeft, OUTPUT);
  pinMode(usSensorTrigPinBackRight, OUTPUT);
  pinMode(usSensorTrigPinFrontCenter, OUTPUT);
  pinMode(usSensorEchoPinFrontLeft, INPUT);
  pinMode(usSensorEchoPinFrontRight, INPUT);
  pinMode(usSensorEchoPinBackLeft, INPUT);
  pinMode(usSensorEchoPinBackRight, INPUT);
  Serial.begin(9600);
}

// motions
void moveForward() {
  servoLeft.write(seLeFoPos);
  servoRight.write(seRiFoPos);
  Serial.print("Forward");
  Serial.println();
}

void moveLeft() {
  servoLeft.write(seLeBaPos);
  servoRight.write(seRiFoPos);
  Serial.print("Left");
  Serial.println();
}

void moveRight() {
  servoLeft.write(seLeFoPos);
  servoRight.write(seRiBaPos);
  Serial.print("Right");
  Serial.println();
}

void moveBackward() {
  servoLeft.write(seLeBaPos);
  servoRight.write(seRiBaPos);
  Serial.print("Backward");
  Serial.println();
}

void stopMoving() {
  servoLeft.write(seLeStPos);
  servoRight.write(seRiStPos);
}

void runUsSensors() {
  // front center
  digitalWrite(usSensorTrigPinFrontCenter, LOW); // clear pin
  delayMicroseconds(2);
  digitalWrite(usSensorTrigPinFrontCenter, HIGH); // set trigger pin on high state for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(usSensorTrigPinFrontCenter, LOW); // set trigger pin on high state for 10 microseconds
  durationFrontCenter = pulseIn(usSensorEchoPinFrontCenter, HIGH); // read pin
  distanceFrontCenter = durationFrontCenter * 0.0133 / 2; // calculate distance inches
  
  // front left
  digitalWrite(usSensorTrigPinFrontLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(usSensorTrigPinFrontLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(usSensorTrigPinFrontLeft, LOW);
  durationFrontLeft = pulseIn(usSensorEchoPinFrontLeft, HIGH);
  distanceFrontLeft = durationFrontLeft * 0.0133 / 2;

  // front right
  digitalWrite(usSensorTrigPinFrontRight, LOW);
  delayMicroseconds(2);
  digitalWrite(usSensorTrigPinFrontRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(usSensorTrigPinFrontRight, LOW);
  durationFrontRight = pulseIn(usSensorEchoPinFrontRight, HIGH);
  distanceFrontRight = durationFrontRight * 0.0133 / 2;
  
  // back left
  digitalWrite(usSensorTrigPinBackLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(usSensorTrigPinBackLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(usSensorTrigPinBackLeft, LOW);
  durationBackLeft = pulseIn(usSensorEchoPinBackLeft, HIGH);
  distanceBackLeft = durationBackLeft * 0.0133 / 2;
  
  // back right
  digitalWrite(usSensorTrigPinBackRight, LOW);
  delayMicroseconds(2);
  digitalWrite(usSensorTrigPinBackRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(usSensorTrigPinBackRight, LOW);
  durationBackRight = pulseIn(usSensorEchoPinBackRight, HIGH);
  distanceBackRight = durationBackRight * 0.0133 / 2;

  // zero obstacle detected
  obstacleDetected = false;

  // check front center
  if (distanceFrontCenter <= obstacleThresholdForward) {
    obstacleDetected = true;
    obstacleDetectedFrontCenter = true; 
  } else {
    obstacleDetectedFrontCenter = false;
  }

  // check front left
  if (distanceFrontLeft <= obstacleThresholdForward) {
    obstacleDetected = true;
    obstacleDetectedFrontLeft = true; 
  } else {
    obstacleDetectedFrontLeft = false;
  }

  // check front right
  if (distanceFrontRight <= obstacleThresholdForward) {
    obstacleDetected = true;
    obstacleDetectedFrontRight = true; 
  } else {
    obstacleDetectedFrontRight = false;
  }

  // check back left
  if (distanceBackLeft <= obstacleThresholdBackward) {
    obstacleDetected = true;
    obstacleDetectedBackLeft = true; 
  } else {
    obstacleDetectedBackLeft = false;
  }

  // check back right
  if (distanceBackRight <= obstacleThresholdBackward) {
    obstacleDetected = true;
    obstacleDetectedBackRight = true; 
  } else {
    obstacleDetectedBackRight = false;
  }

  // print distance
//  Serial.print("dfl: ");
//  Serial.println(distanceFrontLeft);
//  Serial.print("dfr: ");
//  Serial.println(distanceFrontRight);
//  Serial.print("dbl: ");
//  Serial.println(distanceBackLeft);
//  Serial.print("dbr: ");
//  Serial.println(distanceBackRight);
//    Serial.print("Sensor");
//    Serial.println();
}

boolean delayApplied = false;
//int stuckCounter = 0;

void loop() {
  if (!delayApplied) {
    delayApplied = true;
    delay(3000);
  }
  runUsSensors();
  if (!obstacleDetected) {
    moveForward();
  } else if (obstacleDetectedFrontCenter) {
    Serial.print("forward obstruct");
    Serial.println();
    int randomDirection = random(0, 1); // 0 is left, 1 is right
    if(randomDirection == 0) {
      moveLeft();
    } else {
      moveRight();
    }
  } else if (
    obstacleDetectedFrontCenter &&
    obstacleDetectedFrontLeft &&
    obstacleDetectedFrontRight &&
    obstacleDetectedBackLeft &&
    obstacleDetectedBackRight
    ){
    stopMoving(); // cry
  } else if (obstacleDetectedFrontCenter && obstacleDetectedFrontLeft && obstacleDetectedFrontRight){
    moveBackward();
    delay(1500);
  } else if (obstacleDetectedFrontCenter && obstacleDetectedFrontLeft && !obstacleDetectedFrontRight){
    moveRight();
    delay(1000);
  } else if (obstacleDetectedFrontCenter && !obstacleDetectedFrontLeft && obstacleDetectedFrontRight){
    moveLeft();
    delay(1000);
  } else if (obstacleDetectedFrontLeft) {
    moveRight();
  } else if (obstacleDetectedFrontRight) {
    moveLeft();
  } else if (obstacleDetectedBackLeft && obstacleDetectedBackRight){
    moveForward();
    delay(250);
  } else if (obstacleDetectedBackLeft) {
    delay(1000); // stop getting stuck, although forward biased
    moveLeft();
  } else if (obstacleDetectedBackRight) {
    delay(1000);
    moveRight();
  } else {
    stopMoving();
  }
}
