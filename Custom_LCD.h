#pragma once
#include "LiquidCrystal_I2C.h"
#include "Custom_Keypad.h"
#include "Configuration.h"

enum LCD_Mode_t {
  Scale,
  Setting,
  None
};

enum LCD_Display_State_t {
  Scale_Welcome = 0,  // first state of scale
  Scale_Motobike,
  Scale_Car,
  Scale_Overload,    // end state of scale
  Setting_Motobike,  // first state of setting
  Setting_Car,
  Setting_Overload,  // end state of setting
};

class Custom_LCD : public LiquidCrystal_I2C {
public:
  Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void initLCD();

  void displayWeight(int weight);
  void displaySetting();

  void setMode(LCD_Mode_t mode);
  void setDisplayState(LCD_Display_State_t state);
  LCD_Mode_t getMode();
  LCD_Display_State_t getDisplayState();
  void setDisplayStateByWeight(int weight);

  void test();

private:
  LCD_Mode_t mode[2] = { LCD_Mode_t::None, LCD_Mode_t::Scale };  // [0] pre mode, [1] cur mode
  LCD_Display_State_t displayState = LCD_Display_State_t::Scale_Welcome;

protected:
  bool isChangedMode();

  void printBitmap(const unsigned char* bitmap, int x, int y);

  void printWelcome();
  void printMotobike(int weight);
  void printCar(int weight);
  void printOverload(int weight);

  void printSetting_Layout();
  void printSetting_Motobike();
  void printSetting_Car();
  void printSetting_Overload();
};
