int BottomMotorPosPin = A0;
int RightMotorPosPin = A1;
int LeftMotorPosPin = A2;

// Abstracted XY
int curX = 0;
int curY = 0;

// Set by a MIDI Note
int CurPatternFrame = 0;
int MaxSpeed = 255;
int maxValidPattern = 80;
int minValidPattern = 60;
enum PatternType {circleWide      = 60, 
                  circleNormal    = 61, 
                  circleSmall     = 62, 
                  zIn             = 63, 
                  zOut            = 64, 
                  leftRightWide   = 65, 
                  leftRightNormal = 66, 
                  leftRightSmall  = 67, 
                  rightLeftWide   = 68, 
                  rightLeftNormal = 69, 
                  rightLeftSmall  = 70, 
                  upDownWide      = 71, 
                  upDownNormal    = 72, 
                  upDownSmall     = 73,
                  downUpWide      = 74, 
                  downUpNormal    = 75, 
                  downUpSmall     = 76,
                  sendToRight     = 77,
                  sendToLeft      = 78,
                  sendToUp        = 79,
                  sendToDown      = 80
                };
PatternType CurPattern;
boolean RunPattern = false;

struct PatternPoints
{
  int x;
  int y;
  bool zIn = false;
  bool zOut = false;
};

// Pattern Rules:
// * The first -1 encounted as an x or y coordinate indicates an end to the pattern
// * Patterns max out at 300 points.
// * A pattern will only execute when RunPattern is true
#define PATTERN_POINT_LIST_SIZE 300
PatternPoints curPatternPoints [PATTERN_POINT_LIST_SIZE];


int clipSpeed(int speed)
{
  if(speed > MaxSpeed)
    return MaxSpeed;

  return speed;
}

void MoveBottomForward(int speed)
{
    speed = clipSpeed(speed);
    analogWrite(3, speed);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}

void MoveBottomBackward(int speed)
{
    speed = clipSpeed(speed);
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
    speed = clipSpeed(speed);
    analogWrite(6, speed);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void MoveLeftBackward(int speed)
{
    speed = clipSpeed(speed);
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
    speed = clipSpeed(speed);
    analogWrite(9, speed);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
}

void MoveRightBackward(int speed)
{
    speed = clipSpeed(speed);
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

#define THRESHOLD_POS 10
#define THRESHOLD_ACCELERATION 20
#define MAX_SPEED 255
int leftForwardPos = 200;
int leftBackwardPos = 800;
int leftCurrentPos = 0;
int leftCommandedPos = 0;
int leftThresholdPos = THRESHOLD_POS;
int leftMillisStartMotion = 0;
boolean leftInMotion = false;

int rightForwardPos = 200;
int rightBackwardPos = 800;
int rightCurrentPos = 0;
int rightCommandedPos = 0;
int rightThresholdPos = THRESHOLD_POS;
int rightMillisStartMotion = 0;
boolean rightInMotion = false;

int bottomForwardPos = 200;
int bottomBackwardPos = 800;
int bottomCurrentPos = 0;
int bottomCommandedPos = 0;
int bottomThresholdPos = THRESHOLD_POS;
int bottomMillisStartMotion = 0;
boolean bottomInMotion = false;

int globalMaxX = 1024;
int globalMaxY = 1024;
int centerX = 512;
int centerY = 512;

void MoveBottomToPos(int position)
{
  if(position > bottomBackwardPos)
    position = bottomBackwardPos;
  else if(position < bottomForwardPos)
    position = bottomForwardPos;

  bottomCommandedPos = position;

  if(!bottomInMotion)
    bottomMillisStartMotion = millis();
}

void MoveLeftToPos(int position)
{
  if(position > leftBackwardPos)
    position = leftBackwardPos;
  else if(position < leftForwardPos)
    position = leftForwardPos;

  leftCommandedPos = position;

  if(!leftInMotion)
    leftMillisStartMotion = millis();
}

void MoveRightToPos(int position)
{
  if(position > rightBackwardPos)
    position = rightBackwardPos;
  else if(position < rightForwardPos)
    position = rightForwardPos;

  rightCommandedPos = position;

  if(!rightInMotion)
    rightMillisStartMotion = millis();
}

void MoveX(int position)
{
  MoveLeftToPos(position);
  MoveRightToPos(globalMaxX - position);
}

void MoveY(int position)
{
  MoveBottomToPos(position);
}

void MoveBottomMotor()
{
  bottomCurrentPos = ReadBottomMotorPos();

  int speed = millis() - bottomMillisStartMotion;
  speed = speed / 4;

  if(!bottomInMotion && ( (bottomCommandedPos < bottomCurrentPos - bottomThresholdPos) || (bottomCommandedPos > bottomCurrentPos + bottomThresholdPos)))
  {
    bottomInMotion = true;
  }
  else if(bottomCurrentPos < bottomCommandedPos)
  {
    MoveBottomBackward(speed);
  }
  else if(bottomCurrentPos > bottomCommandedPos)
  {
    MoveBottomForward(speed);
  }
  else
  {
    bottomInMotion = false;
    if(!RunPattern)
      StopBottom();
  }
}

void MoveRightMotor()
{
  rightCurrentPos = ReadRightMotorPos();

  int speed = millis() - rightMillisStartMotion;
  speed = speed / 4;

  // Do not attempt to move until the commanded position exceeds the threshold
  if(!rightInMotion && ((rightCommandedPos < rightCurrentPos - rightThresholdPos) || (rightCommandedPos > rightCurrentPos + rightThresholdPos)) )
  {
      rightInMotion = true;
  }
  else if(rightCurrentPos < rightCommandedPos)
  {
    MoveRightBackward(speed);
  }
  else if(rightCurrentPos > rightCommandedPos)
  {
    MoveRightForward(speed);
  }
  else
  {
    rightInMotion = false;
    if(!RunPattern)
      StopRight();
  }
}

void MoveLeftMotor()
{
  leftCurrentPos = ReadLeftMotorPos();

  int speed = millis() - leftMillisStartMotion;
  speed = speed / 4;

  // Do not attempt to move until the commanded position exceeds the threshold
  if(!leftInMotion && ((leftCommandedPos < leftCurrentPos - leftThresholdPos) || (leftCommandedPos > leftCurrentPos + leftThresholdPos)) )
  {
      leftInMotion = true;
  }
  else if(leftCurrentPos < leftCommandedPos)
  {
    MoveLeftBackward(speed);
  }
  else if(leftCurrentPos > leftCommandedPos)
  {
    MoveLeftForward(speed);
  }
  else
  {
    leftInMotion = false;
    if(!RunPattern)
      StopLeft();
  }
}

void MoveToCenter()
{
  // Move To Center
  MoveX(centerX);
  MoveY(centerY);
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

enum controlEnum{moveY = 1, moveX = 2};
void OnControlChange(byte channel, byte control, byte value) {
  
  if(control == moveY)
  {
    RunPattern = false;
    MoveY(map(value, 0, 127, 1024, 0));
  }
  else if(control == moveX)
  {
    RunPattern = false;
    digitalWrite(13, HIGH);
    MoveX(map(value, 0,127, 0, 1024));
  } 

}

// Start at Middle C and move up
void OnNoteOn(byte channel, byte note, byte velocity)
{
  MaxSpeed = map(velocity, 0, 127, 0, 255);

  Serial.print("Note Received: ");
  Serial.println(note);
  Serial.print("Velocity: ");
  Serial.println(velocity);

  if(note >= minValidPattern && note <= maxValidPattern)
  {
    RunPattern = true;
    CurPatternFrame = 0;
    if(note == circleWide)
      CalculateCircleWidePattern();
    else if(note == circleNormal)
      CalculateCircleNormalPattern();
    else if(note == circleSmall)
      CalculateCircleSmallPattern();
    else if(note == zIn)
      CalculateZinPattern();
    else if(note == zOut)
      CalculateZOutPattern();
    else if(note == leftRightWide)
      CalculateLeftRightWidePattern();
    else if(note == leftRightNormal)
      CalculateLeftRightNormalPattern();
    else if(note == leftRightSmall)
      CalculateLeftRightSmallPattern();
    else if(note == upDownWide)
      CalculateUpDownWidePattern();
    else if(note == upDownNormal)
      CalculateUpDownNormalPattern();
    else if(note == upDownSmall)
      CalculateUpDownSmallPattern();
    else if(note == sendToDown)
      CalculateDownPattern(800);
    else if(note == sendToUp)
      CalculateDownPattern(200);
    else if(note == sendToRight)
      CalculateRightPattern(200);
    else if(note == sendToLeft)
      CalculateRightPattern(800);
  }

}

// Pattern Calculations
void FillEmptyPatternSlots(int startSlot)
{
  for(int i = startSlot; i < PATTERN_POINT_LIST_SIZE; i++)
  {
    PatternPoints nullPoint;
    nullPoint.x = -1;
    nullPoint.y = -1;
    curPatternPoints[i] = nullPoint;
  }
}

void CalculateDownPattern(int maxY)
{
  PatternPoints myPoint;
  myPoint.x = centerX;
  myPoint.y = maxY;

  curPatternPoints[0] = myPoint;

  FillEmptyPatternSlots(1);
}

void CalculateRightPattern(int maxX)
{
    PatternPoints myPoint;
  myPoint.x = maxX;
  myPoint.y = centerY;

  curPatternPoints[0] = myPoint;

  FillEmptyPatternSlots(1);
}

void CalculateLeftRightPattern(int maxX)
{
  PatternPoints myPoint;
  myPoint.x = maxX;
  myPoint.y = centerY;
  myPoint.zIn = false;
  myPoint.zOut =false;
  curPatternPoints[0] = myPoint;
  myPoint.x = globalMaxX - maxX;
  myPoint.y = centerY;
  myPoint.zIn = false;
  myPoint.zOut =false;
  curPatternPoints[1] = myPoint;

  FillEmptyPatternSlots(2);
}

void CalculateLeftRightWidePattern()
{
  CalculateLeftRightPattern(600);
}

void CalculateLeftRightNormalPattern()
{
  CalculateLeftRightPattern(400);
}

void CalculateLeftRightSmallPattern()
{
  CalculateLeftRightPattern(200);
}

void CalculateUpDownPattern(int maxY)
{
  PatternPoints myPoint;
  myPoint.x = centerX;
  myPoint.y = maxY;
  myPoint.zIn = false;
  myPoint.zOut =false;
  curPatternPoints[0] = myPoint;
  myPoint.x = centerX;
  myPoint.y = globalMaxY - maxY;
  myPoint.zIn = false;
  myPoint.zOut =false;
  curPatternPoints[1] = myPoint;

  FillEmptyPatternSlots(2);
}

void CalculateUpDownWidePattern()
{
  CalculateUpDownPattern(600);
}

void CalculateUpDownNormalPattern()
{
  CalculateUpDownPattern(400);
}

void CalculateUpDownSmallPattern()
{
  CalculateUpDownPattern(200);
}

void CalculateZinPattern()
{
  PatternPoints myPoint;
  myPoint.zIn = true;
  curPatternPoints[0] = myPoint;

  FillEmptyPatternSlots(1);
}

void CalculateZOutPattern()
{
  PatternPoints myPoint;
  myPoint.zOut = true;
  curPatternPoints[0] = myPoint;

  FillEmptyPatternSlots(1);
}

void CalculateCirclePattern(int radius)
{
  int count = 0;
  for(double i = 0; i < 360; i+= 30)
  {
    double radAngle = (i*3.14159)/180;
    int x = centerX + radius*cos(radAngle);
    int y = centerY + radius*sin(radAngle);
    Serial.println("Start Circle");
    Serial.println(radAngle);
    Serial.println(x);
    Serial.println(y);

    PatternPoints myPoint;
    myPoint.x = x;
    myPoint.y = y;
    myPoint.zIn = false;
    myPoint.zOut =false;
    curPatternPoints[count] = myPoint;
    count++;
  }

  FillEmptyPatternSlots(count);
}

void CalculateCircleWidePattern()
{
  CalculateCirclePattern(200);
}

void CalculateCircleNormalPattern()
{
  CalculateCirclePattern(100);
}

void CalculateCircleSmallPattern()
{
  CalculateCirclePattern(50);
}

void ExecutePattern()
{

  if(!rightInMotion && !leftInMotion && !bottomInMotion)
  {
    Serial.println("Execute Next Frame");

    PatternPoints thePoint = curPatternPoints[CurPatternFrame];

    if(thePoint.zIn)
    {
      MoveRightToPos(rightForwardPos);
      MoveLeftToPos(leftForwardPos);
      MoveBottomToPos(bottomForwardPos);
      Serial.println("Move Z In");
    }
    else if(thePoint.zOut)
    {
      MoveRightToPos(rightBackwardPos);
      MoveLeftToPos(leftBackwardPos);
      MoveBottomToPos(bottomBackwardPos);
      Serial.println("Move Z Out");
    }
    else if(thePoint.x < 0 || thePoint.y < 0)
    {
      CurPatternFrame = 0;
      Serial.println("Reset Frame Count");
    }
    else
    {
      MoveX(thePoint.x);
      MoveY(thePoint.y);
      CurPatternFrame++;

      Serial.print("Execute Frame: ");
      Serial.print(CurPatternFrame);
      Serial.print("  DestX: "); 
      Serial.print(thePoint.x);
      Serial.print("  DestY: "); 
      Serial.println(thePoint.y);
    }

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
  usbMIDI.setHandleNoteOn(OnNoteOn);

  //InitMotors();
  MoveToCenter();
}

void loop() {

  if(RunPattern)
  {
    ExecutePattern();
  }

  // put your main code here, to run repeatedly:
  MoveBottomMotor();
  MoveRightMotor();
  MoveLeftMotor();
  usbMIDI.read();
}
