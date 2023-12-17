#pragma once
#include "LiquidCrystal_I2C.h"
#include "Custom_Keypad.h"

enum LCD_DISPLAY_MODE {
  Welcome,
  Motobike,
  Car,
  Overload,
  Setting,
  Exist
};

class Custom_LCD : public LiquidCrystal_I2C {
public:
  Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void initLCD();

  void printBitmap(const unsigned char* bitmap, int x, int y);
  void printWelcome();
  void printMotobike(long weight);
  void printCar(long weight);
  void printOverload(long weight);

  void displayWeight(long weight);
  void displaySetting();
  void test();

  void setCurrentDisplayMode(LCD_DISPLAY_MODE mode);
  LCD_DISPLAY_MODE getCurrentDisplayMode();
  void setCurrentDisplayModeByWeight(long weight);

private:
  LCD_DISPLAY_MODE currentDisplayMode = LCD_DISPLAY_MODE::Welcome;
  LCD_DISPLAY_MODE previousDisplayMode = -1;

  void updatePreviousMode();
  bool isChangedMode();
  void printSetting_Layout();
  void printSetting_Motobike();
  void printSetting_Car();
  // void printSetting_Overload();
};
