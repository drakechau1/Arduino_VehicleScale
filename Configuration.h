#pragma once
#include "ArduinoLog.h"
#include "DefineEnums.h"
#include <EEPROM.h>

#define ADDR_MOTO_THRESHOLD 1
#define ADDR_CAR_THRESHOLD 4

#define MAX_SCALE_VALUE 20000  // kg

class Configuration {
public:
  void begin();

  void setMode(Mode_t curMode);
  void setMode(Mode_t preMode, Mode_t curMode);
  void setSettingState(Setting_State_t state);
  void setMotoThreshold(int threshold);
  void setCarThreshold(int threshold);
  int getMotoThreshold();
  int getCarThreshold();
  Mode_t getMode();
  Setting_State_t getSettingState();

  bool isChangedMode();
  void updateScaleState(Setting_State_t state);
  void nextSettingState();

protected:
  void getWeightThresholdsFromMem();
private:
  Mode_t mode[2];  // [0] pre state, [1] cur state
  Setting_State_t settingState;
  Scale_Display_t scaleState;
  int weightThresholds[2];  // fist of Moto, another of Car::: 20kg < moto < car < overload < 20000kg
};

// extern Configuration configure;