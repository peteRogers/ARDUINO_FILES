#include <Wire.h>
#include <VL53L0X.h>
#include <I2CRecovery.h>   

VL53L0X distanceSensor;

void setup() {
  i2cRecoverBus(Wire1);
  Serial.begin(115200);
  Wire.begin();
  distanceSensor.setTimeout(500);
  if (!distanceSensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  Serial.println("sensor started");
}

void loop() {
  // put your main code here, to run repeatedly:
 //int dist =  distanceSensor.readRangeContinuousMillimeters();
  int dist = distanceSensor.readRangeSingleMillimeters();
  Serial.println(dist);
  delay(10);
}
