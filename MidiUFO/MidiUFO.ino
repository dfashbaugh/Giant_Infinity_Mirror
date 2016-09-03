#define USE_OCTOWS2811

#include<OctoWS2811.h>
#include<FastLED.h>
#include "CommonVariables.h"
#include "mappings.h"
#include "utils.h"
#include "patterns.h"

/* Helper functions */

//Input a rateue 0 to 384 to get a color rateue.
//The colours are a transition r - g -b - back to r

unsigned int mPattern_to_patternByte(byte incomingByte)
{
  switch (incomingByte) {
    case 0:
      return 68;
      break;
    case 1:
      return 69;
      break;
    case 2:
      return 70;
      break;
    case 3:
      return 62;
      break;
    case 4:
      return 63;
      break;
    case 5:
      return 64;
      break;
    case 6:
      return 65;
      break;
    case 7:
      return 66;
      break;
    case 8:
      return 71;
      break;
    case 9:
      return 72;
      break;
    case 10:
      return 73;
      break;
    case 11:
      return 74;
      break;
    case 12:
      return 75;
      break;
    case 13:
      return 76;
      break;
    case 14:
      return 77;
      break;
    case 15:
      return 78;
      break;
    case 16:
      return 79;
      break;
    case 17:
      return 80;
      break;
    default:
      return 0;
      break;
  }


}

void setColors()
{
  color1 = myColor(r1, g1, b1);
  color2 = myColor(r2, g2, b2);
}

void hideAll() {
  for (int i = 0; i < totalLEDs; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}

void showAll() {
  LEDS.show();
}


void ledCheck(){
  int f = 0;
  int s = 6;
  while(f < 300){
      for(int i = 0; i < totalLEDs; i++){
        if ((i + f)/s % s < s/2){
          leds[i] = CRGB(255,255,0);
        }
        else
        leds[i] = CRGB(0,0,255);
      }

      LEDS.show();
      f++;
      delay(20);
  }

}

enum controlEnum{setRate = 1, setRed = 2};
void OnControlChange(byte channel, byte control, byte value) {
  
  boolean colorChanged = false;

  if(control == setRate)
  {
    rate = map(value, 0, 127, 0, 255);
  }
  else if(control == setRed)
  {
    r1 = map(value, 0, 127, 0, 255);
    colorChanged = true;
  }

  if(colorChanged)
  {
    setColors();
  }

}

byte currentCommandBuf [READBUFFERSIZE];

void setup() {

  pinMode(13, OUTPUT);
  Serial.begin(115200);

  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP).setCorrection( 0x9FFAF0 );;
  LEDS.setBrightness(255);

  ledCheck();

  setColors();

  hideAll();
  showAll();

  patterns[62] = &flickerStrobeTwo;
  patterns[63] = &flickerStrobeFour;
  patterns[64] = &totesRandom;
  patterns[65] = &rainbowCycle;
  patterns[66] = &rainbow;
  // 67 = pause
  // 68 = off
  patterns[69] = &solidColor;
  patterns[70] = &gradient;
  patterns[71] = &pulseSine;
  patterns[72] = &pulseSaw;
  patterns[73] = &bounce;
  patterns[74] = &colorWipe;
  patterns[75] = &colorAlternator;
  patterns[76] = &stripe;
  patterns[77] = &colorChase;
  patterns[78] = &colorWipeMeter;
  patterns[79] = &colorWipeMeterGradient;
  patterns[80] = &pulseOnce;

  rate = 122;
  // pattern = &pulseOnce;
  pattern = &gradient;

  mIndBrightness = 255;



  r1 = 255;
  g1 = 0;
  b1 = 0;
  
  r2 = 0;
  g2 = 0;
  b2 = 0;
  
  //singleColor has black second color
  setColors();
  
  rate = mRate + 1;

  if (patternByte != NULL_PATTERN && patterns[patternByte] != NULL) {
      isOff = false;
      pattern = patterns[69];
      pattern(-2, 0); // On select initialization
  }

  // Reset frame if pattern change
  if(patternByte != lastPattern)
  {
    lastPattern = patternByte;
    frame = 1000000;
  }



  pattern(-2, 0);

  usbMIDI.setHandleControlChange(OnControlChange);
}

void loop() {

  usbMIDI.read();

  int usedRate = 128-rate;
  mCurrentFrameCount += abs(usedRate);
  
  if(mCurrentFrameCount >= NUM_STEPS_PER_FRAME)
  {
    int framesToMove = mCurrentFrameCount/NUM_STEPS_PER_FRAME;
    mCurrentFrameCount = mCurrentFrameCount - framesToMove*NUM_STEPS_PER_FRAME;
    
    frame += usedRate < 0 ? -1*framesToMove : framesToMove;  
  }

  if (frame != lastFrame)
    pattern(-1, 0); // Per frame initialization

  lastFrame = frame;

  for (int i = 0; i < totalLEDs; i++) {

    uint32_t color = pattern(frame, i);

    uint8_t r = ((color & 0xFF0000) >> 16);
    uint8_t g = ((color & 0x00FF00) >> 8);
    uint8_t b = ((color & 0x0000FF));

    //TODO change setbrightness only on change
    if (mIndBrightness < 1.0) {
      r *= mIndBrightness;
      g *= mIndBrightness;
      b *= mIndBrightness;
    }

    float whiteDimmer = 0.7;

    if (r == g && g == b) {
      r *= whiteDimmer;
      g *= whiteDimmer;
      b *= whiteDimmer;
    }

    leds[i] = CRGB(r, g, b); 
  }

  if (isOff) {
    hideAll();
  }

  showAll();

  if (frame >= MAX_FRAME) {
    frame = 0;
  }

  if (light)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);

  light = !light;

}

