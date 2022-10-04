#include <FastLED.h>
#include <OneButton.h>

#define numLeds 120
#define ledPin 2
#define buttonPin 6

const int prPin = A0;

CRGB leds[numLeds];

uint8_t patternCounter = 0;
uint8_t hue = 0;

// Push button connected between pin 7 and GND (no resistor required)
OneButton btn = OneButton(buttonPin, true, true);

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, ledPin, GRB>(leds, numLeds);
  FastLED.setBrightness(50);
  Serial.begin(57600);

  btn.attachClick(nextPattern);

  pinMode(prPin, INPUT);
}

void loop() {
  int prStatus = analogRead(prPin);

  if (prStatus <= 300) {
    FastLED.setBrightness(50);

  } else {
    FastLED.setBrightness(0);
  }

  switch (patternCounter) {
    case 0:
      staticRed();
      break;
    case 1:
      staticBlue();
      break;
    case 2:
      staticGreen();
      break;
    case 3:
      staticPurple();
      break;
    case 4:
      rainbowHue();
      break;
    case 5:
      rainbowBeat();
      break;
  }

  FastLED.show();
  btn.tick();
}

void nextPattern() {
  patternCounter = (patternCounter + 1) % 6;  // Change the number after the % to the number of patterns you have
}

//------- Put your patterns below -------//

void staticRed() {
  fill_solid(leds, numLeds, CRGB::Red);
  FastLED.show();
}


void staticGreen() {
  fill_solid(leds, numLeds, CRGB::Green);
  FastLED.show();
}

void staticBlue() {
  fill_solid(leds, numLeds, CRGB::Blue);
  FastLED.show();
}

void staticPurple() {
  fill_solid(leds, numLeds, CRGB::Purple);
  FastLED.show();
}





void movingDots() {

  uint16_t posBeat = beatsin16(30, 0, numLeds - 1, 0, 0);
  uint16_t posBeat2 = beatsin16(60, 0, numLeds - 1, 0, 0);

  uint16_t posBeat3 = beatsin16(30, 0, numLeds - 1, 0, 32767);
  uint16_t posBeat4 = beatsin16(60, 0, numLeds - 1, 0, 32767);

  // Wave for LED color
  uint8_t colBeat = beatsin8(45, 0, 255, 0, 0);

  leds[(posBeat + posBeat2) / 2] = CHSV(colBeat, 255, 255);
  leds[(posBeat3 + posBeat4) / 2] = CHSV(colBeat, 255, 255);

  fadeToBlackBy(leds, numLeds, 10);
}


void rainbowBeat() {

  uint16_t beatA = beatsin16(30, 0, 255);
  uint16_t beatB = beatsin16(20, 0, 255);
  fill_rainbow(leds, numLeds, (beatA + beatB) / 2, 8);
}

void rainbowHue() {
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CHSV(hue + (i * 10), 255, 255);
  }

  EVERY_N_MILLISECONDS(15) {
    hue++;
  }

  FastLED.show();
}



void redWhiteBlue() {

  uint16_t sinBeat = beatsin16(30, 0, numLeds - 1, 0, 0);
  uint16_t sinBeat2 = beatsin16(30, 0, numLeds - 1, 0, 21845);
  uint16_t sinBeat3 = beatsin16(30, 0, numLeds - 1, 0, 43690);

  leds[sinBeat] = CRGB::Blue;
  leds[sinBeat2] = CRGB::Red;
  leds[sinBeat3] = CRGB::White;

  fadeToBlackBy(leds, numLeds, 10);
}