#include <Wire.h>
#include <RDA5807.h>

RDA5807 rx;

// Potentiometer wiring: outer legs to 5V and GND, middle leg (wiper) to the pin below
#define TUNE_POT   A0   // tunes the frequency
#define VOLUME_POT A1   // sets the volume

// FM band limits in units of 10 kHz (8750 = 87.5 MHz, 10800 = 108.0 MHz)
#define FREQ_MIN  8750
#define FREQ_MAX  10800
#define FREQ_STEP 10    // 100 kHz steps (UK/Europe spacing)

#define POT_DEADBAND 4  // ignore pot changes smaller than this to stop jitter

int lastTuneRaw = -100;
int lastVolumeRaw = -100;
float freq = 0.0;

// Average several readings so the frequency doesn't flicker between stations
int readPot(int pin) {
  long total = 0;
  for (int i = 0; i < 8; i++) {
    total += analogRead(pin);
  }
  return total / 8;
}

void setup() {
  Serial.begin(9600);
  Serial.println("FM receiver starting...");

  // DEBUG: check the radio module answers on I2C (RDA5807 uses address 0x10/0x11)
  Wire.begin();
  Wire.beginTransmission(0x10);
  if (Wire.endTransmission() == 0) {
    Serial.println("Radio module found on I2C");
  } else {
    Serial.println("Radio module NOT found - check SDA/SCL, VCC and GND wiring");
  }

  //radio setup
  rx.setup(); // Starts the receiver with default parameters
  rx.setLnaPortSel(3);  // Trying improve sensitivity.
  rx.setAFC(true);      // Sets Automatic Frequency Control
  rx.setFmDeemphasis(1); //sorts for Europe broadcasting
  rx.setFrequency(9730); // Starting frequency - the tuning pot takes over straight away
  rx.setVolume(4);
}

void loop() {
  // --- Tuning pot ---
  int tuneRaw = readPot(TUNE_POT);
  if (abs(tuneRaw - lastTuneRaw) > POT_DEADBAND) {
    lastTuneRaw = tuneRaw;
    int steps = (FREQ_MAX - FREQ_MIN) / FREQ_STEP;            // number of stations across the band
    // Pots rarely reach exactly 0 or 1023, so treat the last few counts at each end as fully turned
    int step = constrain(map(tuneRaw, 10, 1010, 0, steps), 0, steps);
    int newFreq = FREQ_MIN + step * FREQ_STEP;
    if (newFreq != rx.getFrequency()) {
      rx.setFrequency(newFreq);
      showStatus();
      Serial.print("Frequency: ");
      Serial.print(freq, 1);
      Serial.println(" MHz");
    }
  }

  // --- Volume pot ---
  int volumeRaw = readPot(VOLUME_POT);
  if (abs(volumeRaw - lastVolumeRaw) > POT_DEADBAND) {
    lastVolumeRaw = volumeRaw;
    int newVolume = map(volumeRaw, 0, 1023, 0, 15);           // RDA5807 volume range is 0-15
    if (newVolume != rx.getVolume()) {
      rx.setVolume(newVolume);
      Serial.print("Volume: ");
      Serial.println(newVolume);
    }
  }

  // DEBUG: print the raw pot readings twice a second (remove once it's working)
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 500) {
    lastDebug = millis();
    Serial.print("DEBUG tune pot=");
    Serial.print(tuneRaw);
    Serial.print("  volume pot=");
    Serial.print(volumeRaw);
    Serial.print("  radio freq=");
    Serial.println(rx.getFrequency() / 100.0, 1);
  }

  delay(50);
}

void showStatus() {
 freq = rx.getFrequency()/100.0;
}
