#include "EEPROM.h"
#include "Configuration.h"

void Configuration::begin() {
  Log.infoln("Setup configurations..");

  // setMotoThreshold(200);
  // setCarThreshold(500);

  // getWeightThresholdsFromMem();

  Log.infoln("Setup configurations done.");
  Log.infoln("Moto threshold: %d", getMotoThreshold());
  Log.infoln("Car threshold: %d", getCarThreshold());
}

/**
* Getters, Setters
**/
void Configuration::setMotoThreshold(int value) {
  value = value > MAX_SCALE_VALUE ? MAX_SCALE_VALUE : value;
  EEPROM.put(ADDR_MOTO_THRESHOLD, value);
  Log.infoln("Set moto threshold success");
}

void Configuration::setCarThreshold(int value) {
  value = value > MAX_SCALE_VALUE ? MAX_SCALE_VALUE : value;
  EEPROM.put(ADDR_CAR_THRESHOLD, value);
  Log.infoln("Set car threshold success");
}

int Configuration::getMotoThreshold() {
  int threshold;
  EEPROM.get(ADDR_MOTO_THRESHOLD, threshold);
  return threshold;
}

int Configuration::getCarThreshold() {
  int threshold;
  EEPROM.get(ADDR_CAR_THRESHOLD, threshold);
  return threshold;
}

// void Configuration::getWeightThresholdsFromMem() {
//   EEPROM.get(ADDR_MOTO_THRESHOLD, weightThresholds);
// }

/**
* Logic functions
**/
