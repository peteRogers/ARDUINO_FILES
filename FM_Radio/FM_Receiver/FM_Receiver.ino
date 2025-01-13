#include <RDA5807.h>
RDA5807 rx; 
long rds_elapsed = millis();
long status_elapsed = millis();

void setup() {
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP); // Arduino pin 4 - Seek station down
  pinMode(5, INPUT_PULLUP); // Arduino pin 5 - Seek station up
  rx.setup(); // Starts the receiver with default parameters
  rx.setLnaPortSel(3);  // Trying improve sensitivity.
  rx.setAFC(true);      // Sets Automatic Frequency Control
  rx.setFmDeemphasis(1); //sorts for Europe broadcasting
  rx.setFrequency(8700); // Tunes in 103.9 MHz  - Switch to your local favorite station
  rx.setVolume(7);
  // RDS setup
  rx.setRDS(true);
  rx.setRdsFifo(true);
  
}
void loop() {
  if (digitalRead(4) == LOW) rx.seek(RDA_SEEK_WRAP,RDA_SEEK_DOWN);
  if (digitalRead(5) == LOW) rx.seek(RDA_SEEK_WRAP,RDA_SEEK_UP);

   
    
  
  delay(200);
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
}

void showStatus() {
  char aux[80];
  sprintf(aux, "\nYou are tuned on %u MHz | RSSI: %3.3u dbUv | Vol: %2.2u | Stereo: %s\n", rx.getFrequency(), rx.getRssi(), rx.getVolume(), (rx.isStereo()) ? "Yes" : "No");
  Serial.print(aux);
  status_elapsed = millis();
}