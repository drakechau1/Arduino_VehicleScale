#include "WString.h"
#include "ArduinoLog.h"
#include "Custom_LCD.h"
#include "define_bitmap.h"

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

int Custom_LCD::getCenterX(int length) {
  if (length > 0) {
    return (20 - length) / 2;
  }
  return 0;
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

  setCursor(DISPLAY_MINMAX_X, DISPLAY_MIN_Y);
  print("Min:");

  byte rightArrow[] = { 0x00, 0x04, 0x02, 0x1F, 0x1F, 0x02, 0x04, 0x00 };

  setCursor(DISPLAY_MINMAX_X, DISPLAY_MAX_Y);
  print("Max:");
  createChar(1, rightArrow);
  setCursor(8, 3);
  write(1);
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
  print("OTO (kg)");

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
void Custom_LCD::printBitmap(int x, int y) {
  setCursor(x + 0, y + 0);
  print(char(0));
  setCursor(x + 1, y + 0);
  print(char(1));
  setCursor(x + 2, y + 0);
  print(char(2));
  setCursor(x + 3, y + 0);
  print(char(3));

  setCursor(x + 0, y + 1);
  print(char(4));
  setCursor(x + 1, y + 1);
  print(char(5));
  setCursor(x + 2, y + 1);
  print(char(6));
  setCursor(x + 3, y + 1);
  print(char(7));
}

void Custom_LCD::setMotoBitmap() {
  createChar(0, moto0);
  createChar(1, moto1);
  createChar(2, moto2);
  createChar(3, moto3);
  createChar(4, moto4);
  createChar(5, moto5);
  createChar(6, moto6);
  createChar(7, moto7);
}
void Custom_LCD::setCarBitmap() {
  createChar(0, car0);
  createChar(1, car1);
  createChar(2, car2);
  createChar(3, car3);
  createChar(4, car4);
  createChar(5, car5);
  createChar(6, car6);
  createChar(7, car7);
}

void Custom_LCD::printScale_Welcome() {
  if (isStateChange()) {
    clear();
    String s = "De tai:";
    int x = getCenterX(s.length());
    setCursor(x, 1);
    print(s);

    s = "CAN TU DONG";
    x = getCenterX(s.length());
    setCursor(x, 2);
    print(s);
  }
}

void Custom_LCD::printScale_Motobike(int weight) {
  if (isStateChange()) {
    clear();
    String s = "XE MAY";
    int x = getCenterX(s.length());
    setCursor(x, 0);
    print(s);

    setMotoBitmap();
    printBitmap(getCenterX(4), 2);
  }
  String s = String(weight) + " kg";
  int x = getCenterX(s.length());
  setCursor(x, 1);
  print(s + "   ");
}

void Custom_LCD::printScale_Car(int weight) {
  if (isStateChange()) {
    clear();
    String s = "OTO";
    int x = getCenterX(s.length());
    setCursor(x, 0);
    print(s);

    setCarBitmap();
    printBitmap(getCenterX(4), 2);
  }
  String s = String(weight) + " kg";
  int x = getCenterX(s.length());
  setCursor(x, 1);
  print(s + "   ");
}

void Custom_LCD::printScale_Overload(int weight) {
  if (isStateChange()) {
    clear();
    String s = "QUA TAI";
    int x = getCenterX(s.length());
    setCursor(x, 0);
    print(s);

    setCarBitmap();
    printBitmap(getCenterX(4), 2);
  }
  String s = String(weight) + " kg";
  int x = getCenterX(s.length());
  setCursor(x, 1);
  print(s + "   ");
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