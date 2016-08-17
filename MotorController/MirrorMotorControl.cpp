#include "MirrorMotorControl.h"

void MirrorMotorControl::SetupMotors()
{
  AFMS = Adafruit_MotorShield(); 
  AFMS.begin();  
  
  bottomMotor = AFMS.getMotor(1);;
  bottom.motor = bottomMotor;
  bottom.destination = 0;

  leftMotor = AFMS.getMotor(2);
  left.motor = leftMotor;
  left.destination = 0;

  rightMotor = AFMS.getMotor(3);
  right.motor = rightMotor;
  right.destination = 0;

  initialize(bottom.motor);
  initialize(left.motor);
  initialize(right.motor);
  delay(12000);
  stopAll();

  driveToCenter();
}

void MirrorMotorControl::MoveMotor(MotorAndPosition &curMotor)
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

void MirrorMotorControl::initialize(Adafruit_DCMotor *motor)
{
  motor->setSpeed(255);
  motor->run(FORWARD);
}

void MirrorMotorControl::reverseInitialize(Adafruit_DCMotor *motor)
{
  motor->setSpeed(255);
  motor->run(BACKWARD);
}

void MirrorMotorControl::driveForwardTime(MotorAndPosition &curMotor, int delayTime)
{
  curMotor.motor->setSpeed(255);
  curMotor.motor->run(FORWARD);
  delay(delayTime);
  curMotor.motor->run(RELEASE);
}

void MirrorMotorControl::driveBackwardTime(MotorAndPosition &curMotor, int delayTime)
{
    curMotor.motor->setSpeed(255);
    curMotor.motor->run(BACKWARD);
    delay(delayTime);
    curMotor.motor->run(RELEASE);
}

void MirrorMotorControl::driveBackward(MotorAndPosition &curMotor)
{
    curMotor.motor->setSpeed(255);
    curMotor.motor->run(BACKWARD);
}

void MirrorMotorControl::driveForward(MotorAndPosition &curMotor)
{
  curMotor.motor->setSpeed(255);
  curMotor.motor->run(FORWARD);
}

void MirrorMotorControl::stopAll()
{
  left.motor->run(RELEASE);
  bottom.motor->run(RELEASE);
  right.motor->run(RELEASE);
}

void MirrorMotorControl::driveToCenter()
{
  driveBackward(left);
  driveBackward(right);
  driveBackward(bottom);
  delay(5000);
  stopAll();
}

void MirrorMotorControl::MoveToXYZ(int x, int y, int z)
{
  bottom.destination = y + z;
  left.destination = x + z;
  right.destination = -x + z;
}

void MirrorMotorControl::MoveMotors()
{
  MoveMotor(bottom);
  MoveMotor(left);
  MoveMotor(right);
}

void MirrorMotorControl::DriveCircles()
{
  // RIGHT
  driveForward(left);
  driveBackward(right);
  delay(5000);
  stopAll();

  // LEFT
  driveForward(right);
  driveBackward(left);
  delay(5000);
  stopAll();

  // DOWN
  driveBackward(bottom);
  delay(5000);
  stopAll();

  // DOWN RIGHT
  driveForward(left);
  driveBackward(right);
  delay(5000);
  stopAll();

  // DOWN LEFT
  driveForward(right);
  driveBackward(left);
  delay(10000);
  stopAll();

  // UP LEFT
  driveForward(bottom);
  delay(10000);
  stopAll();

  // UP RIGHT
  driveForward(left);
  driveBackward(right);
  delay(10000);
  stopAll();

  // Back to center
  driveForward(right);
  driveBackward(left);
  driveBackward(bottom);
  delay(5000);
  stopAll();

}