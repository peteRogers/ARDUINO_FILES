# ARDUINO_FILES

```Arduino

#include <Bounce2.h>
Bounce buttonA = Bounce();

void setup() {
  buttonA.attach( 8 ,  INPUT_PULLUP );
  buttonA.interval(20);
  Serial.begin(9600);
}

void loop() {
  buttonA.update();
  if (buttonA.fell() ) {
      Serial.println("pressed");
  }
  if ( buttonA.rose() ) {
      Serial.println("depressed");
  }
}

```

## FM Radio 
```Arduino
#include <RDA5807.h>
#include <Bounce2.h>
Bounce buttonUp = Bounce();
Bounce buttonDown = Bounce();
RDA5807 rx; 
float freq = 0.0;


void setup() {
  Serial.begin(9600);
  //buttons
  buttonUp.attach(7, INPUT_PULLUP); // Arduino pin 7 - Seek station up
  buttonDown.attach(8, INPUT_PULLUP); // Arduino pin 8 - Seek station down
  buttonUp.interval(20);
  buttonDown.interval(20);
  //radio setup
  rx.setup(); // Starts the receiver with default parameters
  rx.setLnaPortSel(3);  // Trying improve sensitivity.
  rx.setAFC(true);      // Sets Automatic Frequency Control
  rx.setFmDeemphasis(1); //sorts for Europe broadcasting
  rx.setFrequency(9730); // Tunes in 103.9 MHz  - Switch to your local favorite station
  rx.setVolume(4);

}
void loop() {
  // buttonUp.update();
  // buttonDown.update();
  // if (buttonUp.fell()) {
  //   rx.seek(RDA_SEEK_WRAP,RDA_SEEK_DOWN, showStatus);
  // }
  // if (buttonDown.fell()) {
  //   rx.seek(RDA_SEEK_WRAP,RDA_SEEK_UP, showStatus);
  // }
  freq = rx.getFrequency()/100.0;
  Serial.println(freq);
  delay(50);
 
}

void showStatus() {
  char aux[80];
  sprintf(aux, "\nYou are tuned on %u MHz | RSSI: %3.3u dbUv | Vol: %2.2u | Stereo: %s\n", rx.getFrequency(), rx.getRssi(), rx.getVolume(), (rx.isStereo()) ? "Yes" : "No");
  Serial.print(aux);
}

/*
 if (Serial.available() > 0) {
    char key = Serial.read();
    switch (key) {
      case '+':
        rx.setVolumeUp();
        break;
      case '-':
        rx.setVolumeDown();
        break;
      case 'U':
      case 'u':
        rx.setFrequencyUp();
        break;
      case 'D':
      case 'd':
        rx.setFrequencyDown();
        break;
      case 'S':
        rx.seek(RDA_SEEK_WRAP, RDA_SEEK_UP, showStatus);
        break;
      case 's':
        rx.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN, showStatus);
        break;
      default:
        break;
    }
  }
  */
  ```