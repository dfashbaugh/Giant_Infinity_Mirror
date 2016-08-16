#include <Wire.h>
#include "MirrorMotorControl.h"

MirrorMotorControl theController;

// MIDI Control Code
enum controlEnum{moveY = 1, moveX = 2, moveZ = 3, LEDEffect = 4};
int  currentYDestination = 0;
int  currentXDestination = 0;
int  currentZDestination = 0;
void OnControlChange(byte channel, byte control, byte value) {

  control = control - 1;
  
  if(control == moveY)
  {
    currentYDestination = value;
  }
  else if(control == moveX)
  {
    currentXDestination = value;
  }
  else if(control == moveZ)
  {
    currentZDestination = value;
  }

  theController.MoveToXYZ(currentXDestination, currentYDestination, currentZDestination);
}

void setup() {
  Serial.begin(9600);           
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  theController.SetupMotors();

  usbMIDI.setHandleControlChange(OnControlChange);
}


void loop() {

  theController.MoveMotors();
}


