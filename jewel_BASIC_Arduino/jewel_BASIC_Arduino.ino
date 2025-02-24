#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel jewel = Adafruit_NeoPixel(7, 7, NEO_GRBW + NEO_KHZ800);

void setup() {
  jewel.begin();
}

void loop() {
  jewel.setPixelColor(0, 0, 0, 0, 255);
  jewel.show();
}



//function to get color from one number
uint32_t Spectrum(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return jewel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return jewel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return jewel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}