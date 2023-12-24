#pragma once
#include "ArduinoLog.h"
#include "DefineEnums.h"
#include <EEPROM.h>

#define ADDR_MOTO_THRESHOLD 1
#define ADDR_CAR_THRESHOLD 10

class Configuration {
public:
  void begin();
  void setMotoThreshold(int threshold);
  void setCarThreshold(int threshold);
  int getMotoThreshold();
  int getCarThreshold();

// private:
  // int weightThresholds[2];  // fist of Moto, second of Car::: 20kg < moto < car < overload < 20000kg
  // void getWeightThresholdsFromMem();
};

// extern Configuration configure;