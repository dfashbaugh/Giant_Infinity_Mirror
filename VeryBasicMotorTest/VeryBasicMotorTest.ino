int BottomMotorPosPin = A0;
int RightMotorPosPin = A1;
int LeftMotorPosPin = A2;

void MoveBottomForward()
{
    analogWrite(3, 255);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}

void MoveBottomBackward()
{
    analogWrite(3, 255);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void StopBottom()
{
  analogWrite(3, 0);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void MoveLeftForward()
{
    analogWrite(6, 255);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void MoveLeftBackward()
{
    analogWrite(6, 255);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
}

void StopLeft()
{
  analogWrite(6, 0);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void MoveRightForward()
{
    analogWrite(9, 255);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
}

void MoveRightBackward()
{
    analogWrite(9, 255);
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

#define THRESHOLD_POS 20
int leftForwardPos = 0;
int leftBackwardPos = 0;
int leftCurrentPos = 0;
int leftCommandedPos = 0;
int leftThresholdPos = THRESHOLD_POS;

int rightForwardPos = 0;
int rightBackwardPos = 0;
int rightCurrentPos = 0;
int rightCommandedPos = 0;
int rightThresholdPos = THRESHOLD_POS;

int bottomForwardPos = 0;
int bottomBackwardPos = 0;
int bottomCurrentPos = 0;
int bottomCommandedPos = 0;
int bottomThresholdPos = THRESHOLD_POS;

void MoveBottomToPos(int position)
{
  bottomCommandedPos = position;
}

void MoveLeftToPos(int position)
{
  leftCommandedPos = position;
}

void MoveRightToPos(int position)
{
  rightCommandedPos = position;
}

void MoveBottomMotor()
{
  bottomCurrentPos = ReadBottomMotorPos();

  if(bottomCurrentPos < bottomCommandedPos - bottomThresholdPos)
  {
    MoveBottomBackward();
  }
  else if(bottomCurrentPos > bottomCommandedPos + bottomThresholdPos)
  {
    MoveBottomForward();
  }
  else
  {
    StopBottom();
  }
}

void MoveRightMotor()
{
  rightCurrentPos = ReadRightMotorPos();

  if(rightCurrentPos < rightCommandedPos - rightThresholdPos)
  {
    MoveRightBackward();
  }
  else if(rightCurrentPos > rightCommandedPos + rightThresholdPos)
  {
    MoveRightForward();
  }
  else
  {
    StopRight();
  }
}

void MoveLeftMotor()
{
  leftCurrentPos = ReadLeftMotorPos();

  if(leftCurrentPos < leftCommandedPos - leftThresholdPos)
  {
    MoveLeftBackward();
  }
  else if(leftCurrentPos > leftCommandedPos + leftThresholdPos)
  {
    MoveLeftForward();
  }
  else
  {
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
  MoveLeftBackward();
  MoveBottomBackward();
  MoveRightBackward();

  delay(4000);
  leftBackwardPos = ReadLeftMotorPos();
  rightBackwardPos = ReadRightMotorPos();
  bottomBackwardPos = ReadBottomMotorPos();

  MoveLeftForward();
  MoveBottomForward();
  MoveRightForward();

  delay(4000);
  leftForwardPos = ReadLeftMotorPos();
  rightForwardPos = ReadRightMotorPos();
  bottomForwardPos = ReadBottomMotorPos();

  MoveToCenter();
}

void setup() {
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

  Serial.begin(9600);
  Serial.println("Begin Initialization");
  InitMotors();
  Serial.println("Initialization Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  MoveBottomMotor();
  MoveRightMotor();
  MoveLeftMotor();

  if(Serial.available())
  {
    char theChar = Serial.read();
    Serial.print("Found ");
    Serial.println(theChar);
    
    if(theChar == 't')
    {
      MoveBottomForward();
    }
    else if(theChar == 'y')
    {
      MoveBottomBackward();
    }
    else if(theChar == 'u')
    {
      Serial.println(ReadBottomMotorPos());
    }
    else if(theChar == 'g')
    {
      MoveLeftForward();
    }
    else if(theChar == 'h')
    {
      MoveLeftBackward();
    }
    else if(theChar == 'j')
    {
      Serial.println(ReadLeftMotorPos());
    }
    else if(theChar == 'b')
    {
      MoveRightForward();
    }
    else if(theChar == 'n')
    {
      MoveRightBackward();
    }
    else if(theChar == 'm')
    {
      Serial.println(ReadRightMotorPos());
    }

    else if(theChar == 'w')
    {
      MoveBottomToPos(bottomCommandedPos - 20);
    }
    else if(theChar == 's')
    {
      MoveBottomToPos(bottomCommandedPos + 20);
    }
    else if(theChar == 'a')
    {
      MoveLeftToPos(leftCommandedPos + 20);
      MoveRightToPos(rightCommandedPos - 20);
    }
    else if(theChar == 'd')
    {
      MoveLeftToPos(leftCommandedPos - 20);
      MoveRightToPos(rightCommandedPos + 20);
    }
    else if(theChar == 'c')
    {
      MoveToCenter();
    }
  }

  //Serial.println(analogRead(A0));
  
}
