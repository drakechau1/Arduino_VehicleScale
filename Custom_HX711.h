// https://github.com/bogde/HX711
#pragma once
#include "HX711.h"

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3

// Adjustment settings
#define LOADCELL_OFFSET 50682624
#define LOADCELL_DIVIDER 5895655

class Custom_HX711 {
private:
  HX711 hx711;

public:
  void init();
  long getValue();
};