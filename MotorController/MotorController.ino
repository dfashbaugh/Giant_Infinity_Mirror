/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

struct MotorAndPosition
{
  Adafruit_DCMotor* motor;
  int destination;
  int curPosition;
  int velocity;
};

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *bottomLeftMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
Adafruit_DCMotor *bottomRightMotor = AFMS.getMotor(4);
Adafruit_DCMotor *topLeftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *topRightMotor = AFMS.getMotor(1);

MotorAndPosition bottomLeft;
MotorAndPosition bottomRight;
MotorAndPosition topLeft;
MotorAndPosition topRight;

// P Controller gain
int p = 10;

void initialize(Adafruit_DCMotor *motor)
{
  motor->setSpeed(255);
  motor->run(FORWARD);
}

void reverseInitialize(Adafruit_DCMotor *motor)
{
  motor->setSpeed(255);
  motor->run(BACKWARD);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  
  bottomLeft.motor = bottomLeftMotor;
  bottomLeft.destination = 0;
  bottomRight.motor = bottomRightMotor;
  bottomRight.destination = 0;
  topLeft.motor = topLeftMotor;
  topLeft.destination = 0;
  topRight.motor = topRightMotor;
  topRight.destination = 0;

  initialize(bottomLeft.motor);
  initialize(bottomRight.motor);
  initialize(topLeft.motor);
  initialize(topRight.motor);
  delay(12000);
  topRight.motor->run(RELEASE);
  topLeft.motor->run(RELEASE);
  bottomRight.motor->run(RELEASE);
  bottomLeft.motor->run(RELEASE);

  driveToCenter();
  driveCircles();

  //driveForwardTime(topRight, 1000);

  // Set the speed to start, from 0 (off) to 255 (max speed)
  //myMotor->setSpeed(150);
  //myMotor->run(FORWARD);
  // turn on motor
  //myMotor->run(RELEASE);
  //myMotor->run(BACKWARD);
}

void MoveMotor(MotorAndPosition &curMotor)
{
  curMotor.curPosition = 0; // Read in the position

  int positionError = curMotor.curPosition - curMotor.destination;

  if(positionError == 0)
  {
    curMotor.motor->run(RELEASE);
    return;
  }

  int velocity = positionError*p;
  curMotor.motor->setSpeed(velocity);
  if(positionError < 0)
    curMotor.motor->run(BACKWARD);
  else
    curMotor.motor->run(FORWARD);

}

void driveForwardTime(MotorAndPosition &curMotor, int delayTime)
{
  curMotor.motor->setSpeed(255);
  curMotor.motor->run(FORWARD);
  delay(delayTime);
  curMotor.motor->run(RELEASE);
}

void driveBackwardTime(MotorAndPosition &curMotor, int delayTime)
{
    curMotor.motor->setSpeed(255);
    curMotor.motor->run(BACKWARD);
    delay(delayTime);
    curMotor.motor->run(RELEASE);
}

void driveBackward(MotorAndPosition &curMotor)
{
    curMotor.motor->setSpeed(255);
    curMotor.motor->run(BACKWARD);
}

void driveForward(MotorAndPosition &curMotor)
{
  curMotor.motor->setSpeed(255);
  curMotor.motor->run(FORWARD);
}

void stopAll()
{
  topLeft.motor->run(RELEASE);
  bottomRight.motor->run(RELEASE);
  topRight.motor->run(RELEASE);
  bottomLeft.motor->run(RELEASE);
}

void driveToCenter()
{
  driveBackward(topLeft);
  driveBackward(topRight);
  driveBackward(bottomLeft);
  driveBackward(bottomRight);
  delay(5000);
  stopAll();
}

void driveCircles()
{
  driveBackward(topLeft);
  driveForward(bottomRight);
  delay(5000);
  driveForward(topLeft);
  driveBackward(bottomRight);
  delay(10000);
  driveBackward(topLeft);
  driveForward(bottomRight);
  delay(5000);
  stopAll();
  
  driveBackward(topRight);
  driveForward(bottomLeft);
  delay(5000);
  driveForward(topRight);
  driveBackward(bottomLeft);
  delay(10000);
  driveBackward(topRight);
  driveForward(bottomLeft);
  delay(5000);
  stopAll();
}

void loop() {
  // To Set Position
  //bottomLeft.destination = "YOUR POSITION"  

  //MoveMotor(bottomLeft);
  //MoveMotor(bottomRight);
  //MoveMotor(topLeft);
  //MoveMotor(topRight);
}
