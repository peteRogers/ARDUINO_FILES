  /*Connections:
    pin 10: to pin 11 on other arduino : RX
    pin 11: to pin 10 on other arduino : TX
    GND ---> GND on other arduino
  */

#include <SoftwareSerial.h>

// setup software Serial
SoftwareSerial arduino2Serial(10, 11); // RX, TX

void setup() {
  // Start Serial communication with the computer
  Serial.begin(9600);
  //Start SoftwareSerial communication with other arduino
  arduino2Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // Forward data from the computer to Arduino 
  if (Serial.available()) {
    char data = Serial.read();
    arduino2Serial.write(data);//sends data from computer to the other arduino
  }

  // Forward data from Arduino to the computer
  if (arduino2Serial.available()) {
    char data = arduino2Serial.read();
    if(data == 's'){
      //do something
    }
    Serial.print(data);
  }
}