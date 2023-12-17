// #define DISABLE_LOGGING
// #define ENABLE_TEST
#include "ArduinoLog.h"
#include "Custom_LCD.h"
#include "Custom_HX711.h"
#include "Custom_Keypad.h"


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
  lcd.test();
  scale.test();
#endif
}

void loop() {
#ifndef ENABLE_TEST  // release mode

  char settingKey = keypad.getKey();

  // Setting mode
  if (settingKey == '#') {
    lcd.setCurrentDisplayMode(LCD_DISPLAY_MODE::Setting);
    lcd.displaySetting();

    while (lcd.getCurrentDisplayMode() == LCD_DISPLAY_MODE::Setting) {
      long weight = 0;
      char enteredKey = '\0';
      while (enteredKey != '*'
             && lcd.getCurrentDisplayMode() == LCD_DISPLAY_MODE::Setting) {  // ok key
        enteredKey = keypad.getKey();

        // ascii: '0' -> 48, '9' -> 57
        if (enteredKey >= '0' && enteredKey <= '9') {
          weight = weight * 10 + (long)(enteredKey - 48);
          Log.infoln("weight = %d", weight);
        } else if (enteredKey == '#') {  // exist setting mode
          lcd.setCurrentDisplayMode(LCD_DISPLAY_MODE::Welcome);
        }
      }
    }
  } else {  // Scale mode
    long weight = scale.getWeight();
    lcd.setCurrentDisplayModeByWeight(weight);
    lcd.displayWeight(weight);
  }

#else  // test mode
  // keypad.test();
  // scale.test();
#endif
}
