#include <FastLED.h>

#define LED_PIN 33
#define NUM_LEDS 200
#define LED_TYPE WS2811
#define COLOR_ORDER BRG

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {
  for (int i = 0; i <=10; i++) {
    leds[i] = CRGB::Red; // Set LED to red
  }
  FastLED.show();
  delay(1000);

  for (int i = 11; i <=20; i++) {
     leds[i] = CRGB::DeepPink; 
  }
   for (int i = 21; i <=30; i++) {
     leds[i] = CRGB::Red; 
  }

  for (int i = 31; i <=40; i++) {
     leds[i] = CRGB::Green; 
  }
  FastLED.show();
  delay(1000);
}
