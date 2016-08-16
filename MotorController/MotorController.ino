#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

struct MotorAndPosition
{
  Adafruit_DCMotor* motor;
  int destination;
  int curPosition;
  int velocity;
  int pGain;
};

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *bottomMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);

MotorAndPosition bottom;
MotorAndPosition left;
MotorAndPosition right;

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
  
  bottom.motor = bottomMotor;
  bottom.destination = 0;
  left.motor = leftMotor;
  left.destination = 0;
  right.motor = rightMotor;
  right.destination = 0;

  initialize(bottom.motor);
  initialize(left.motor);
  initialize(right.motor);
  delay(12000);
  stopAll();

  driveToCenter();
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

  int velocity = positionError*curMotor.pGain;
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
  left.motor->run(RELEASE);
  bottom.motor->run(RELEASE);
  right.motor->run(RELEASE);
}

void driveToCenter()
{
  driveBackward(left);
  driveBackward(right);
  driveBackward(bottom);
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
