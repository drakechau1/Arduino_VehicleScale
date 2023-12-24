#include "ArduinoLog.h"
#include "Custom_LCD.h"

extern Configuration configure;

Custom_LCD::Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
  : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) {
}

void Custom_LCD::initLCD() {
  init();
  backlight();
}

/**
*
* Logic functions
*
**/
bool Custom_LCD::isChangedMode() {
  if (mode[0] == mode[1]) {
    return false;
  }
  mode[0] = mode[1];  // update previousMode
  return true;
}

bool Custom_LCD::isChangedState() {
  if (displayState[0] == displayState[1]) {
    return false;
  }
  displayState[0] = displayState[1];  // update previousdisplayState
  return true;
}

/**
*
* Setters, Getters
*
**/
void Custom_LCD::setDisplayStateByWeight(int weight) {
  if (weight < 3) {
    setDisplayState(LCD_Display_State_t::Scale_Welcome);
  } else if (weight < configure.getMotoThreshold()) {
    setDisplayState(LCD_Display_State_t::Scale_Motobike);
  } else if (weight < configure.getCarThreshold()) {
    setDisplayState(LCD_Display_State_t::Scale_Car);
  } else {
    setDisplayState(LCD_Display_State_t::Scale_Overload);
  }
}

void Custom_LCD::setDisplayState(LCD_Display_State_t state) {
  displayState[1] = state;
}

void Custom_LCD::setMode(LCD_Mode_t mode) {
  this->mode[1] = mode;
}

LCD_Display_State_t Custom_LCD::getDisplayState() {
  return displayState[0];
}

LCD_Mode_t Custom_LCD::getMode() {
  return mode[1];  // current mode
}

/**
*
* Setting mode display
*
**/
void Custom_LCD::printSetting_Layout() {
  setCursor(0, 0);
  print("CAI DAT");

  setCursor(0, 2);
  print("* Luu");

  setCursor(0, 3);
  print("# Thoat");

  //  char I[] = { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 };
  char I[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
  createChar(0, I);
  for (int i = 0; i < 4; i++) {
    setCursor(7, i);
    write(0);
  }

  switch (displayState[1]) {
    case LCD_Display_State_t::Setting_Motobike:
      printSetting_Motobike();
      break;
    case LCD_Display_State_t::Setting_Car:
      printSetting_Car();
      break;
    case LCD_Display_State_t::Setting_Overload:
      printSetting_Overload();
      break;
  }
}

void Custom_LCD::printSetting_Motobike() {
  setCursor(9, 0);
  print("Xe may (kg)");

  setCursor(9, 2);
  print("Min");
  setCursor(9, 3);
  print(3);

  setCursor(16, 2);
  print("Max");
  setCursor(16, 3);
  print(configure.getMotoThreshold());
}

void Custom_LCD::printSetting_Car() {
  setCursor(9, 0);
  print("Xe oto (kg)");

  setCursor(9, 2);
  print("Min");

  setCursor(16, 2);
  print("Max");

  setCursor(9, 3);
  print(configure.getMotoThreshold());

  setCursor(16, 3);
  print(configure.getCarThreshold());
}

void Custom_LCD::printSetting_Overload() {
  setCursor(9, 0);
  print("Qua tai");

  setCursor(9, 2);
  print("Min");

  setCursor(16, 2);
  print("Max");

  setCursor(9, 3);
  print("> ");
  print(configure.getCarThreshold());
  print(" (kg)");
}

void Custom_LCD::displaySetting() {
  // if (isChangedMode()) {
  //   clear();
  //   printSetting_Layout();
  // }

  if (isChangedState()) {
    clear();
    printSetting_Layout();
    switch (displayState[1]) {
      case LCD_Display_State_t::Setting_Motobike:
        printSetting_Motobike();
        break;
      case LCD_Display_State_t::Setting_Car:
        printSetting_Car();
        break;
      case LCD_Display_State_t::Setting_Overload:
        printSetting_Overload();
        break;
    }
  }
}

/**
*
* Scale mode display
*
**/
void Custom_LCD::printBitmap(const char* bitmap, int x, int y) {
}

void Custom_LCD::printWelcome() {
  if (isChangedState()) {
    clear();
    setCursor(0, 0);
    print("CAN TU DONG");
  }
}

void Custom_LCD::printMotobike(int weight) {
  if (isChangedState()) {
    clear();
    setCursor(0, 0);
    print("XE MAY");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::printCar(int weight) {
  if (isChangedState()) {
    clear();
    setCursor(0, 0);
    print("XE OTO");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::printOverload(int weight) {
  if (isChangedState()) {
    clear();
    setCursor(0, 0);
    print("QUA TAI");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::displayWeight(int weight) {
  setDisplayStateByWeight(weight);
  switch (displayState[1]) {
    case LCD_Display_State_t::Scale_Welcome:
      printWelcome();
      break;
    case LCD_Display_State_t::Scale_Motobike:
      printMotobike(weight);
      break;
    case LCD_Display_State_t::Scale_Car:
      printCar(weight);
      break;
    case LCD_Display_State_t::Scale_Overload:
      printOverload(weight);
      break;
  }
}

/**
*
* Test functions
*
**/
void Custom_LCD::test() {
  // Print a message to the LCD.
  setCursor(3, 0);
  print("Hello, world!");
  setCursor(2, 1);
  print("Ywrobot Arduino!");
  setCursor(0, 2);
  print("Arduino LCM IIC 2004");
}