#pragma once
#include "LiquidCrystal_I2C.h"
#include "Custom_Keypad.h"
#include "Configuration.h"
// #include "define_bitmap.h"

#define DISPLAY_MINMAX_X 10
#define DISPLAY_MIN_Y 2
#define DISPLAY_MAX_Y 3



class Custom_LCD : public LiquidCrystal_I2C {
public:
  Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void initLCD();

  bool isStateChange();

  void displayScale(int weight);
  void displaySetting();

  void setDisplayState(int newState);
  int getDisplayState();

  void test();

private:
  int displayState[2] = { INIT, INIT };

  int getCenterX(int length);

public:
  void printBitmap(int x, int y);
  void setMotoBitmap();
  void setCarBitmap();

  void printScale_Welcome();
  void printScale_Motobike(int weight);
  void printScale_Car(int weight);
  void printScale_Overload(int weight);

  void printSetting_Layout();
  void printSetting_Motobike();
  void printSetting_Car();
  void printSetting_Overload();
};
