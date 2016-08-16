#ifndef MOTORCONTROL
#define MOTORCONTROL

#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
class MirrorMotorControl
{
private:
	Adafruit_MotorShield AFMS;

	struct MotorAndPosition
	{
	  Adafruit_DCMotor* motor;
	  int destination;
	  int curPosition;
	  int velocity;
	  int pGain;
	};
	
	// Select which 'port' M1, M2, M3 or M4. In this case, M1
	Adafruit_DCMotor *bottomMotor;
	Adafruit_DCMotor *leftMotor;
	Adafruit_DCMotor *rightMotor;
	
	MotorAndPosition bottom;
	MotorAndPosition left;
	MotorAndPosition right;

	void MoveMotor  		(MotorAndPosition &curMotor);
	void initialize 		(Adafruit_DCMotor *motor);
	void reverseInitialize 	(Adafruit_DCMotor *motor);
	void driveBackward   	(MotorAndPosition &curMotor);
	void driveForward 		(MotorAndPosition &curMotor);
	void driveForwardTime 	(MotorAndPosition &curMotor, int delayTime);
	void driveBackwardTime	(MotorAndPosition &curMotor, int delayTime);

public:
	MirrorMotorControl () {};
	~MirrorMotorControl() {};

	void SetupMotors();
	void MoveMotors ();

	void MoveToXYZ 		(int x, int y, int z);
	void driveToCenter 	();
	void stopAll 		();
};

#endif