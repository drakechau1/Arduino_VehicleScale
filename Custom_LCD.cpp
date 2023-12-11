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

void Custom_LCD::initLCD() {
  init();
  backlight();
}

void Custom_LCD::printBitmap(const unsigned char* bitmap, int x, int y) {
}

void Custom_LCD::printNormal() {
  if (isChangedMode()) {
    clear();
    setCursor(0, 0);
    print("CAN TU DONG");
  }
}
void Custom_LCD::printMotobike(long weight) {
  if (isChangedMode()) {
    clear();
    setCursor(0, 0);
    print("XE MAY");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}
void Custom_LCD::printCar(long weight) {
  if (isChangedMode()) {
    clear();
    setCursor(0, 0);
    print("XE OTO");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}
void Custom_LCD::printOverload(long weight) {
  if (!isChangedMode()) {
    clear();
    setCursor(0, 0);
    print("QUA TAI");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::displayWeight(long weight) {
  setCurrentDisplayModeByWeight(weight);
  switch (currentDisplayMode) {
    default:
    case LCD_DISPLAY_MODE::Normal:
      printNormal();
      break;
    case LCD_DISPLAY_MODE::Motobike:
      printMotobike(weight);
      break;
    case LCD_DISPLAY_MODE::Car:
      printCar(weight);
      break;
    case LCD_DISPLAY_MODE::Overload:
      printOverload(weight);
      break;
  }
}

void Custom_LCD::displaySetting() {
  setCurrentDisplayMode(LCD_DISPLAY_MODE::Setting);
  if (isChangedMode()) {
    clear();
    printSetting_Layout();
  }
}

void Custom_LCD::setCurrentDisplayMode(LCD_DISPLAY_MODE mode) {
  currentDisplayMode = mode;
}

void Custom_LCD::updatePreviousMode() {
  previousDisplayMode = currentDisplayMode;
}


void Custom_LCD::setCurrentDisplayModeByWeight(long weight) {
  if (weight < 3) {
    setCurrentDisplayMode(LCD_DISPLAY_MODE::Normal);
  } else if (weight < 100) {
    setCurrentDisplayMode(LCD_DISPLAY_MODE::Motobike);
  } else if (weight < 200) {
    setCurrentDisplayMode(LCD_DISPLAY_MODE::Car);
  } else {
    setCurrentDisplayMode(LCD_DISPLAY_MODE::Overload);
  }
}

bool Custom_LCD::isChangedMode() {
  if (currentDisplayMode == previousDisplayMode) {
    return false;
  }
  updatePreviousMode();
  return true;
}

void Custom_LCD::printSetting_Layout() {
  setCursor(0, 0);
  print("CAI DAT");

  setCursor(0, 2);
  print("* OK");

  setCursor(0, 3);
  print("# Thoat");

  unsigned char I[] = { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 };
  createChar(0, I);
  for (int i = 0; i < 4; i++) {
    setCursor(7, i);
    write(0);
  }
}