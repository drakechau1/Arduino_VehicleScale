// https://github.com/Chris--A/Keypad/blob/master/examples/CustomKeypad/CustomKeypad.ino
#pragma once
#include <Keypad.h>
#include "ArduinoLog.h"

#define ROWS 4  //four rows
#define COLS 4  //four columns

enum Key_t {
  EXIST = '#',
  OK = '*'
};

class Custom_Keypad : public Keypad {
private:
  //define the cymbols on the buttons of the keypads
  char hexaKeys[ROWS][COLS] = {
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
  };
  byte _rowPins_[ROWS] = { 11, 10, 9, 8 };  //connect to the row pinouts of the keypad
  byte _colPins_[COLS] = { 7, 6, 5, 4 };  //connect to the column pinouts of the keypad

public:
  Custom_Keypad()
    : Keypad(makeKeymap(hexaKeys), _rowPins_, _colPins_, ROWS, COLS) {
  }

  void test();
};

extern Custom_Keypad keypad;
