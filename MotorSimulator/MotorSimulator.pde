class MotorAndPosition
{
  public int curPosition;
  public int curVelocity;
  public int destination;
  public int backEndPos;
  public int frontEndPos;
};
 
MotorAndPosition bottomLeft;
MotorAndPosition bottomRight;
MotorAndPosition topLeft;
MotorAndPosition topRight;

void initializeMotor(MotorAndPosition theMotor)
{
  theMotor.curPosition = 10;
  theMotor.curVelocity = 0;
  theMotor.destination = 0;
  theMotor.backEndPos = 0;
  theMotor.frontEndPos = 20;
}

void initializeMotors()
{
  bottomLeft = new MotorAndPosition();
  bottomRight = new MotorAndPosition();
  topLeft = new MotorAndPosition();
  topRight = new MotorAndPosition();

  initializeMotor(bottomLeft);
  initializeMotor(bottomRight);
  initializeMotor(topLeft);
  initializeMotor(topRight);
}

// x ranges from -10 -> 10
// y ranges from -10 -> 10
// z ranges from -10 -> 10
void moveToPos(int x, int y, int z)
{
  if( (z + x) < 0 || (z + x) > 20)
    return;
  else if( (z + y) < 0 || (z + y) > 20)
    return;

  bottomLeft.curPosition = z - x;
  bottomRight.curPosition = z + x;
  topLeft.curPosition = z - x;
  topRight.curPosition = z + x;
}

int barWidth = 20;
int lastBar = -1;

void setup() {
  size(640, 360);
  colorMode(HSB, width, 100, width);
  noStroke();
  background(0);

  initializeMotors();
}

void draw() {
  int whichBar = mouseX / barWidth;
  if (whichBar != lastBar) {
    int barX = whichBar * barWidth;
    fill(barX, 100, mouseY);
    rect(barX, 0, barWidth, height);
    lastBar = whichBar;
  }
}