#include <FastLED.h>
#define NUM_LEDS 2      /* The amount of pixels/leds you have */
#define DATA_PIN 3       /* The pin your data line is connected to */
#define LED_TYPE WS2812B /* I assume you have WS2812B leds, if not just change it to whatever you have */
#define BRIGHTNESS 255   /* Control the brightness of your leds */
#define SATURATION 255   /* Control the saturation of your leds */

CRGB leds[NUM_LEDS];
int zaman = millis();
int zaman2 = zaman;

#include <Keyboard.h>

// use this option for OSX:
char ctrlKey = KEY_LEFT_GUI;
// use this option for Windows and Linux:
//  char ctrlKey = KEY_LEFT_CTRL;

int i = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  i++;
  zaman=millis();
  if (!digitalRead(5) && !digitalRead(6)) {
    if (zaman > zaman2 + 1000) {
      Keyboard.press(' ');
      delay(5);
      Keyboard.release(' ');
      delay(100);
      Keyboard.press('m');
      while (!digitalRead(5) && !digitalRead(6));
    }
  }
  else {
  zaman2=zaman;
  }
  Keyboard.release('m');

  if (digitalRead(5) == HIGH) {
    Keyboard.release('d');  // do nothing until pin 2 goes low
    leds[0] = CHSV(i / 13 + 20, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
  else {
    // new document:
    Keyboard.press('d');
    leds[0] = CHSV(i / 13 + 120, SATURATION, BRIGHTNESS);
    FastLED.show();
    delay(3);
  }
  if (digitalRead(6) == HIGH) {
    Keyboard.release('s');  // do nothing until pin 2 goes lowdssddsdssddsdssddsdssddsdsdsdsds
    leds[1] = CHSV(i / 13, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
  else {
    // new document:
    Keyboard.press('s');
    leds[1] = CHSV(i / 13 + 120, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
  if (i == 255 * 13) {
    i = 0;
  }
}
