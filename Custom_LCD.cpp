#include "Custom_LCD.h"

Custom_LCD::Custom_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
  : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) {
}

void Custom_LCD::test() {
  // Print a message to the LCD.
  setCursor(3, 0);
  print("Hello, world!");
  setCursor(2, 1);
  print("Ywrobot Arduino!");
  setCursor(0, 2);
  print("Arduino LCM IIC 2004");
  setCursor(2, 3);
  print("Power By Ec-yuan!");
}

void Custom_LCD::printBitmap(const unsigned char* bitmap, int x, int y) {
}

void Custom_LCD::printMotobike(float weight) {
}
void Custom_LCD::printCar(float weight) {
}
void Custom_LCD::printOverload(float weight) {
}
