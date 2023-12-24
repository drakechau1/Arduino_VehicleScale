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
* Logic functions
**/
bool Custom_LCD::isStateChange() {
  if (displayState[0] == displayState[1]) {
    return false;
  }
  displayState[0] = displayState[1];  // update previous state
  return true;
}

/**
* Setters, Getters
**/
void Custom_LCD::setDisplayState(int newState) {
  displayState[1] = newState;
}

int Custom_LCD::getDisplayState() {
  return displayState[1];
}

/**
* Setting mode display
**/
void Custom_LCD::printSetting_Layout() {
  setCursor(0, 0);
  print("Cai dat");
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

  setCursor(9, 2);
  print("Min:");

  byte rightArrow[] = { 0x00, 0x04, 0x02, 0x1F, 0x1F, 0x02, 0x04, 0x00 };

  createChar(1, rightArrow);
  setCursor(8, 3);
  write(1);
  print("Max:");
}

void Custom_LCD::printSetting_Motobike() {
  setCursor(9, 0);
  print("Xe may (kg)");

  setCursor(14, 2);
  print(LOWER_THRESHOLD_MOTO);

  setCursor(14, 3);
  print(configure.getMotoThreshold());
}

void Custom_LCD::printSetting_Car() {
  setCursor(9, 0);
  print("Xe oto (kg)");

  setCursor(14, 2);
  print(configure.getMotoThreshold());

  setCursor(14, 3);
  print(configure.getCarThreshold());
}

void Custom_LCD::printSetting_Overload() {
  setCursor(9, 0);
  print("Qua tai(kg)");

  setCursor(14, 2);
  print(configure.getCarThreshold());

  setCursor(14, 3);
  print(MAX_SCALE_VALUE);

  setCursor(8, 3);
  print(" ");  // ereases right arrow display
}

void Custom_LCD::displaySetting() {
  if (isStateChange()) {
    clear();
    printSetting_Layout();
    switch (displayState[1]) {
      case MOTOBIKE:
        printSetting_Motobike();
        break;
      case CAR:
        printSetting_Car();
        break;
      case OVERLOAD:
        printSetting_Overload();
        break;
    }
  }
}

/**
* Scale mode display
**/
void Custom_LCD::printBitmap(const char* bitmap, int x, int y) {
}

void Custom_LCD::printScale_Welcome() {
  if (isStateChange()) {
    clear();
    setCursor(0, 0);
    print("CAN TU DONG");
  }
}

void Custom_LCD::printScale_Motobike(int weight) {
  if (isStateChange()) {
    clear();
    setCursor(0, 0);
    print("XE MAY");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::printScale_Car(int weight) {
  if (isStateChange()) {
    clear();
    setCursor(0, 0);
    print("XE OTO");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::printScale_Overload(int weight) {
  if (isStateChange()) {
    clear();
    setCursor(0, 0);
    print("QUA TAI");
    setCursor(4, 2);
    print("Kg");
  }
  setCursor(0, 2);
  print(weight);
}

void Custom_LCD::displayScale(int weight) {
  // switch (displayState[1]) {
  //   case LCD_Display_State_t::Scale_Welcome:
  //     printWelcome();
  //     break;
  //   case LCD_Display_State_t::Scale_Motobike:
  //     printMotobike(weight);
  //     break;
  //   case LCD_Display_State_t::Scale_Car:
  //     printCar(weight);
  //     break;
  //   case LCD_Display_State_t::Scale_Overload:
  //     printOverload(weight);
  //     break;
  // }
}

/**
* Test functions
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