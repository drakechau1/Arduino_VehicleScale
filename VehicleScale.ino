// #define DISABLE_LOGGING
#include "Custom_HX711.h"
#include "ArduinoLog.h"

void setup() {
  const Custom_HX711 loadcell;
  loadcell.init();
}

void loop() {
}
