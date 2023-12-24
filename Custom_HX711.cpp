#include "ArduinoLog.h"
#include "Custom_HX711.h"

void Custom_HX711::init() {
  // Initialize library
  begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  reset();
}

void Custom_HX711::reset() {
  if (wait_ready_timeout(WAIT_READY_TIMEOUT)) {
    set_scale(LOADCELL_DIVIDER);
    tare();
    Log.infoln("Tare scale done...");
  } else {
    Log.infoln("HX711 not found.");
  }
}

int Custom_HX711::getWeight() {
  if (wait_ready_timeout(WAIT_READY_TIMEOUT)) {
    delay(50);
    return (int)get_units(10);
  } else {
    Log.infoln("HX711 not found.");
  }
}

void Custom_HX711::test() {
  Log.infoln("Weight: %l", getWeight());
}
