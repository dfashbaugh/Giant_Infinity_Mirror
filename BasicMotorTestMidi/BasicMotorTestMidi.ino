int BottomMotorPosPin = A0;
int RightMotorPosPin = A1;
int LeftMotorPosPin = A2;

void MoveBottomForward(int speed)
{
    analogWrite(3, speed);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}

void MoveBottomBackward(int speed)
{
    analogWrite(3, speed);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void StopBottom()
{
  analogWrite(3, 0);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void MoveLeftForward(int speed)
{
    analogWrite(6, speed);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void MoveLeftBackward(int speed)
{
    analogWrite(6, speed);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
}

void StopLeft()
{
  analogWrite(6, 0);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void MoveRightForward(int speed)
{
    analogWrite(9, speed);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
}

void MoveRightBackward(int speed)
{
    analogWrite(9, speed);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
}

void StopRight()
{
  analogWrite(9, 0);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

int ReadBottomMotorPos()
{
  return analogRead(BottomMotorPosPin);
}

int ReadLeftMotorPos()
{
  return analogRead(LeftMotorPosPin);
}

int ReadRightMotorPos()
{
  return analogRead(RightMotorPosPin);
}

#define THRESHOLD_POS 5
#define THRESHOLD_ACCELERATION 20
#define MAX_SPEED 255
int leftForwardPos = 0;
int leftBackwardPos = 1024;
int leftCurrentPos = 0;
int leftCommandedPos = 0;
int leftThresholdPos = THRESHOLD_POS;
int leftMillisStartMotion = 0;
boolean leftInMotion = false;

int rightForwardPos = 0;
int rightBackwardPos = 1024;
int rightCurrentPos = 0;
int rightCommandedPos = 0;
int rightThresholdPos = THRESHOLD_POS;
int rightMillisStartMotion = 0;
boolean rightInMotion = false;

int bottomForwardPos = 0;
int bottomBackwardPos = 1024;
int bottomCurrentPos = 0;
int bottomCommandedPos = 0;
int bottomThresholdPos = THRESHOLD_POS;
int bottomMillisStartMotion = 0;
boolean bottomInMotion = false;

void MoveBottomToPos(int position)
{
  bottomCommandedPos = position;

  if(!bottomInMotion)
    bottomMillisStartMotion = millis();
}

void MoveLeftToPos(int position)
{
  leftCommandedPos = position;

  if(!leftInMotion)
    leftMillisStartMotion = millis();
}

void MoveRightToPos(int position)
{
  rightCommandedPos = position;

  if(!rightInMotion)
    rightMillisStartMotion = millis();
}

void MoveBottomMotor()
{
  bottomCurrentPos = ReadBottomMotorPos();

  int speed = millis() - bottomMillisStartMotion;
  speed = speed / 4;

  bottomInMotion = true;

  if(bottomCurrentPos < bottomCommandedPos - bottomThresholdPos)
  {
    MoveBottomBackward(speed);
  }
  else if(bottomCurrentPos > bottomCommandedPos + bottomThresholdPos)
  {
    MoveBottomForward(speed);
  }
  else
  {
    bottomInMotion = false;
    StopBottom();
  }
}

void MoveRightMotor()
{
  rightCurrentPos = ReadRightMotorPos();

  int speed = millis() - rightMillisStartMotion;
  speed = speed / 4;

  rightInMotion = true;

  if(rightCurrentPos < rightCommandedPos - rightThresholdPos)
  {
    MoveRightBackward(speed);
  }
  else if(rightCurrentPos > rightCommandedPos + rightThresholdPos)
  {
    MoveRightForward(speed);
  }
  else
  {
    rightInMotion = false;
    StopRight();
  }
}

void MoveLeftMotor()
{
  leftCurrentPos = ReadLeftMotorPos();

  int speed = millis() - leftMillisStartMotion;
  speed = speed / 4;

  leftInMotion = true;

  if(leftCurrentPos < leftCommandedPos - leftThresholdPos)
  {
    MoveLeftBackward(speed);
  }
  else if(leftCurrentPos > leftCommandedPos + leftThresholdPos)
  {
    MoveLeftForward(speed);
  }
  else
  {
    leftInMotion = false;
    StopLeft();
  }
}

void MoveToCenter()
{
  // Move To Center
  MoveLeftToPos( (leftBackwardPos + leftForwardPos)/2 );
  MoveRightToPos( (rightBackwardPos + rightForwardPos)/2 );
  MoveBottomToPos( (bottomBackwardPos + bottomForwardPos)/2 );
}

void InitMotors()
{
  MoveLeftBackward(MAX_SPEED);
  MoveBottomBackward(MAX_SPEED);
  MoveRightBackward(MAX_SPEED);

  delay(4000);
  leftBackwardPos = ReadLeftMotorPos();
  rightBackwardPos = ReadRightMotorPos();
  bottomBackwardPos = ReadBottomMotorPos();

  MoveLeftForward(MAX_SPEED);
  MoveBottomForward(MAX_SPEED);
  MoveRightForward(MAX_SPEED);

  delay(4000);
  leftForwardPos = ReadLeftMotorPos();
  rightForwardPos = ReadRightMotorPos();
  bottomForwardPos = ReadBottomMotorPos();

  MoveToCenter();
}

enum controlEnum{moveY = 1, moveX = 2, LEDEffect = 4};
void OnControlChange(byte channel, byte control, byte value) {
  
  if(control == moveY)
  {
    MoveBottomToPos(map(value, 0, 127, 1024, 0));
  }
  else if(control == moveX)
  {
    digitalWrite(13, HIGH);
    MoveLeftToPos(map(value, 0,127, 0, 1024));
    MoveRightToPos(map(value, 0, 127, 1024, 0));
  } 

}

void setup() {

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  // put your setup code here, to run once:
  // MOTOR 1
  pinMode(3, OUTPUT); // PWM
  pinMode(4, OUTPUT); // DIR1
  pinMode(5, OUTPUT); // DIR2

  // MOTOR 2
  pinMode(6, OUTPUT); // PWM
  pinMode(7, OUTPUT); // DIR1
  pinMode(8, OUTPUT); // DIR2

  // MOTOR 3
  pinMode(9, OUTPUT); //PWM
  pinMode(10, OUTPUT); // DIR1
  pinMode(11, OUTPUT); // DIR2

  for(int i = 3; i < 12; i++)
  {
    digitalWrite(i, LOW);
  }

  usbMIDI.setHandleControlChange(OnControlChange);  

  //InitMotors();
  MoveToCenter();
}

void loop() {
  // put your main code here, to run repeatedly:
  MoveBottomMotor();
  MoveRightMotor();
  MoveLeftMotor();
  usbMIDI.read();
}
