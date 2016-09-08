int snake(long frame, int i) {
  return i; 
}

int forward(long frame, int i) {
  return i;
}

int backward(long frame, int i) {
  return totalLEDs - 1 - i;
}

int intoSpace(long frame, int i)
{
  int returnValue = i / NUM_LEDS_PER_STRIP;

  // Case for strips 7-8
  if(returnValue == 7 || returnValue == 9)
  {
    if(i > (NUM_LEDS_PER_STRIP*returnValue) + (NUM_LEDS_PER_STRIP/2) )
      returnValue++;
  }

  // Case for strips 1-6
  return returnValue;
}

int longSnake(long frame, int i)
{
  return i/2;
}

int shortSnake(long frame, int i)
{
  return i*2;
}

int dekonstruktor(long frame, int i)
{
  if(frame%400 > 400)
  {
    return i+(frame%200/30);
  }
  else
  {
    return i + 200/30 - (frame%200/30);
  } 
}

int dekonstruktorRando(long frame, int i)
{
  return i+random(frame%400);
}