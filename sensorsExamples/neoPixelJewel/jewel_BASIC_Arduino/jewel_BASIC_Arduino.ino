#include <Adafruit_NeoPixel.h>

#define PIN 13
Adafruit_NeoPixel jewel = Adafruit_NeoPixel(7, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  jewel.begin();
}

void loop() {
  jewel.setPixelColor(0, 0, 0, 0, 255);
  jewel.show();
}
