#include <Wire.h>
#include <RDA5807M.h>

// Create an instance of the RDA5807 class
RDA5807M radio;
long freq = 10000;
int pFreq = 0;

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  //Serial.println("fokfokf");
  // Initialize the radio module
 if (!radio.initWire(Wire)) {
    Serial.println("no radio chip found.");
    delay(2000);
    //ESP.restart();
  };

  // Set the frequency to 98.1 FM
  //radio.setFrequency(freq); // Tune to 98.1 MHz
  
  //Serial.println("Tuned to 98.1 FM.");
  //radio.setFrequency(8750);
  
  delay(100);
  //radio.setFrequency(freq);
 // setAFC(true); 
}

void loop() {
  // Seek the next available station
  
 // 
  //delay();
  int in = analogRead(A1);
  if(abs(pFreq - in) > 10){
    long l = map(in, 0, 1023, 8700, 12000);
    radio.setFrequency(l);
   // radio.seekUp(true);
    //printRDSInfo();
      float currentFrequency = radio.getFrequency(); // Get the new tuned frequency
      Serial.print("Tuned to: ");
      Serial.print(currentFrequency);
      Serial.println(" MHz");
    pFreq = in; 
  }
  int sen = (analogRead(A0) / 96) - 1;
  //Serial.println(sen);
  //Serial.println(radio.)
  delay(100);
  radio.setVolume(sen);
  if(sen < 0){
    radio.setMute(true);
  }else{
    radio.setMute(false);
  }
  

  // //freq = freq + 20;
  // float currentFrequency = radio.getFrequency(); // Get the new tuned frequency
  //     Serial.print("Tuned to: ");
  //     Serial.print(currentFrequency);
  //     Serial.println(" MHz");

  // // if (Serial.available()) {
  // //   char command = Serial.read();
  // //   if (command == 'u') { // Press 'u' to seek up
  // //     //radio.seekUp();
  // //     radio.setFrequency(freq);
  // //     float currentFrequency = radio.getFrequency(); // Get the new tuned frequency
  // //     Serial.print("Tuned to: ");
  // //     Serial.print(currentFrequency);
  // //     Serial.println(" MHz");
  // //   }
  // // }
}



// ----------------------- AFC Control -------------------------
void setAFC(bool enable) {
  uint16_t reg02 = 0b1100000000000000; // Base for Register 0x02 (Power and Config)
  if (!enable) {
    reg02 |= (1 << 4); // Disable AFC
  }

  Wire.beginTransmission(0x10); // RDA5807M I2C Address
  Wire.write(0x02);             // Register 0x02
  Wire.write(highByte(reg02));
  Wire.write(lowByte(reg02));
  Wire.endTransmission();

  Serial.print("AFC ");
  Serial.println(enable ? "Enabled" : "Disabled");
}
