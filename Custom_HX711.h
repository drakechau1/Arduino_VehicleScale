// https://github.com/bogde/HX711
// https://randomnerdtutorials.com/arduino-load-cell-hx711/
#pragma once
#include "HX711.h"
#include "ArduinoLog.h"

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3

// Adjustment settings
#define LOADCELL_OFFSET 50682624
#define LOADCELL_DIVIDER 5895655

class Custom_HX711 : public HX711 {
public:
  void init();
  void reset();
  long getWeight();

  void test();
};