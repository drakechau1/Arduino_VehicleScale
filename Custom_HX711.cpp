#include "Custom_HX711.h"

void Custom_HX711::init() {
  // Initialize library
  hx711.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // hx711.set_scale(LOADCELL_DIVIDER);
  // hx711.set_offset(LOADCELL_OFFSET);
}

long Custom_HX711::getValue() {
  hx711.get_value(10);
}