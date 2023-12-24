#pragma once
#include "LiquidCrystal_I2C.h"
#include "Custom_Keypad.h"
#include "Configuration.h"

class Custom_LCD : public LiquidCrystal_I2C {
public:
  Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void initLCD();

  void displayScale(int weight);
  void displaySetting();

  void setDisplayState(int newState);
  int getDisplayState();

  void test();

private:
  int displayState[2] = { INIT, INIT };

  bool isStateChange();

public:
  void printBitmap(const char* bitmap, int x, int y);

  void printScale_Welcome();
  void printScale_Motobike(int weight);
  void printScale_Car(int weight);
  void printScale_Overload(int weight);

  void printSetting_Layout();
  void printSetting_Motobike();
  void printSetting_Car();
  void printSetting_Overload();
};
