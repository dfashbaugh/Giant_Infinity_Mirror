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
  // Case for strips 7-8
  if(i > NUM_LEDS_PER_STRIP*6)
  {
    return i / (NUM_LEDS_PER_STRIP/2);
  }

  // Case for strips 1-6
  return i / NUM_LEDS_PER_STRIP;
}