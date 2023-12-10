#include "ArduinoLog.h"
#include "Custom_HX711.h"

void Custom_HX711::init() {
  // Initialize library
  begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // set_scale(LOADCELL_DIVIDER);
  // set_offset(LOADCELL_OFFSET);
}

void Custom_HX711::reset() {
  if (wait_ready_timeout(1000)) {
    tare();
  } else {
    Log.infoln("HX711 not found.");
  }
}

long Custom_HX711::getWeight() {
  if (wait_ready_timeout(1000)) {
    set_scale();
    tare();
    return get_units(10);
  }
  Log.infoln("HX711 not found.");
  return 0;
}

void Custom_HX711::test() {
  if (wait_ready_timeout(1000)) {
    set_scale();
    Log.infoln("Tare... remove any weights from the scale");
    delay(1000);
    reset();
    Log.infoln("Tare done...");
    Log.infoln("Place a known weight on the scale..");
    delay(1000);
    Log.infoln("Result: %d", getWeight());
  } else {
    Log.infoln("HX711 not found.");
  }
  delay(1000);
}