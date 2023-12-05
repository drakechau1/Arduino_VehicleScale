// #define DISABLE_LOGGING
#include "Custom_HX711.h"
#include "ArduinoLog.h"

void setup() {
    // Set up serial port and wait until connected
  Serial.begin(9600);
  while (!Serial && !Serial.available()) {}

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  const Custom_HX711 loadcell;
  loadcell.init();
}

void loop() {
}
