#include <Wire.h>
#include <TDA7419.h>

TDA7419::TDA7419 tda; // default Wire

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TDA7419 Basic example");

  Wire.begin();

  tda.begin(); // pushes defaults

  // Configure a few settings
  tda.setMainSource(TDA7419::InputSource::SE1);
  tda.setInputGain(8);
  tda.setMasterVolume(0);  // 0 dB
  tda.setBassLevel(2);
  tda.setMiddleLevel(0);
  tda.setTrebleLevel(2);

  // Send only the changes
  if (!tda.sendChangedRegisters()) {
    Serial.println("Failed to write changed registers");
  }

  Serial.println("Configured TDA7419");
}

void loop() {
  // add your control logic here
}
