// #define DISABLE_LOGGING
#include "ArduinoLog.h"

void setup() {
  // Set up serial port and wait until connected
  Serial.begin(9600);
  while (!Serial && !Serial.available()) {}

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
}

void loop() {
}
