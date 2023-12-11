// #define DISABLE_LOGGING
// #define ENABLE_TEST
#include "ArduinoLog.h"
#include "Custom_HX711.h"
#include "Custom_Keypad.h"
#include "Custom_LCD.h"


Custom_LCD lcd(0x27, 20, 4);
Custom_HX711 scale;
Custom_Keypad keypad;

void setup() {
  // Set up serial port and wait until connected
  Serial.begin(9600);
  while (!Serial && !Serial.available()) {}

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

#ifndef ENABLE_TEST
  Log.infoln("----------RELEASE MODE----------");
#else
  Log.infoln("----------TEST MODE");
#endif

  lcd.initLCD();
  scale.init();

#ifndef ENABLE_TEST  // release mode

#else  // test mode
  // lcd.test();
#endif
}

void loop() {
#ifndef ENABLE_TEST  // release mode
  char settingKey = keypad.getKey();
  if (settingKey) {
    char existKey = '\0';
    while (existKey != '#') {
      lcd.displaySetting();
      existKey = keypad.getKey();
    }
  } else {
    long weight = scale.getWeight();
    lcd.displayWeight(weight);
  }

#else  // test mode
  // keypad.test();
  // scale.test();
#endif
}
