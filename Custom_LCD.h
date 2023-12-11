#pragma once
#include "LiquidCrystal_I2C.h"

enum LCD_DISPLAY_MODE {
  Normal,
  Motobike,
  Car,
  Overload,
  Setting
};

class Custom_LCD : public LiquidCrystal_I2C {
public:
  Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void initLCD();

  void printBitmap(const unsigned char* bitmap, int x, int y);
  void printNormal();
  void printMotobike(long weight);
  void printCar(long weight);
  void printOverload(long weight);

  void displayWeight(long weight);
  void displaySetting();
  void test();

  void setCurrentDisplayMode(LCD_DISPLAY_MODE mode);
  void setCurrentDisplayModeByWeight(long weight);

private:
  LCD_DISPLAY_MODE currentDisplayMode = LCD_DISPLAY_MODE::Normal;
  LCD_DISPLAY_MODE previousDisplayMode = -1;

  void updatePreviousMode();
  bool isChangedMode();
  void printSetting_Layout();
};
