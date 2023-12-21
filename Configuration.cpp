#include "Configuration.h"

void Configuration::begin() {
  Log.infoln("Init configurations, %X", this);

  // setMotoThreshold(200);
  // setCarThreshold(500);

  setMode(Mode_t::SCALE, Mode_t::SCALE);
  scaleState = Scale_Display_t::SCALE_WELCOME;
  settingState = Setting_State_t::SETTING_MOTOBIKE;

  getWeightThresholdsFromMem();

  Log.infoln("Moto threshold: %d", getMotoThreshold());
  Log.infoln("Car threshold: %d", getCarThreshold());
}

/**
*
* Getters, Setters
*
**/
void Configuration::setMode(Mode_t curMode) {
  mode[1] = curMode;
  Log.infoln("Set mode success");
}

void Configuration::setMode(Mode_t preMode, Mode_t curMode) {
  this->mode[0] = preMode;
  this->mode[1] = curMode;
  Log.infoln("Set mode success.");
}

void Configuration::setSettingState(Setting_State_t state) {
  settingState = state;
}

void Configuration::setMotoThreshold(int threshold) {
  weightThresholds[0] = threshold;
  EEPROM.put(ADDR_MOTO_THRESHOLD, weightThresholds);
  Log.infoln("Set moto threshold success");
}

void Configuration::setCarThreshold(int threshold) {
  weightThresholds[1] = threshold;
  EEPROM.put(ADDR_MOTO_THRESHOLD, weightThresholds);
  Log.infoln("Set car threshold success");
}

int Configuration::getMotoThreshold() {
  return weightThresholds[0];
}

int Configuration::getCarThreshold() {
  return weightThresholds[1];
}

Mode_t Configuration::getMode() {
  return mode[1];
}

Setting_State_t Configuration::getSettingState() {
  return settingState;
}

void Configuration::getWeightThresholdsFromMem() {
  EEPROM.get(ADDR_MOTO_THRESHOLD, weightThresholds);
}

/**
*
* Logic functions
*
**/
bool Configuration::isChangedMode() {
  if (mode[0] == mode[1]) {
    return false;
  }
  mode[0] = mode[1];  // update previous state
  return true;
}

void Configuration::nextSettingState() {
  settingState = settingState + 1;
  if (settingState > Setting_State_t::SETTING_OVERLOAD)
    settingState = Setting_State_t::SETTING_MOTOBIKE;
}
