#pragma once
#include "LiquidCrystal_I2C.h"

class Custom_LCD : public LiquidCrystal_I2C {
public:
  Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void printBitmap(const unsigned char* bitmap, int x, int y);
  void printMotobike(float weight);
  void printCar(float weight);
  void printOverload(float weight);

  void test();

private:
};