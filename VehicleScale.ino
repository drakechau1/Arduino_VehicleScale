// #define DISABLE_LOGGING
// #define ENABLE_TEST
#include "ArduinoLog.h"
#include "Configuration.h"
#include "Custom_LCD.h"
#include "Custom_HX711.h"
#include "Custom_Keypad.h"


Custom_LCD lcd(0x27, 20, 4);
Custom_HX711 scale;
Custom_Keypad keypad;
Configuration configure;

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

  configure.begin();
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

  // Setting key -> Setting mode
  if (settingKey == '#') {
    configure.setMode(Mode_t::SETTING);
    configure.setSettingState(Setting_State_t::SETTING_MOTOBIKE);

    lcd.displaySetting();

    // setting configure
    while (configure.getMode() == Mode_t::SETTING) {
      unsigned int weight = 0;
      char enteredKey = keypad.getKey();

      while (enteredKey != '*') {  // OK key
        enteredKey = keypad.getKey();

        // ascii: '0' -> 48, '9' -> 57
        if (enteredKey >= '0' && enteredKey <= '9') {
          weight = weight * 10 + (unsigned int)(enteredKey - 48);        // Concat chars to unsigned int
          weight = weight > MAX_SCALE_VALUE ? MAX_SCALE_VALUE : weight;  // Constrains value with max value is MAX_SCALE_VALUE (20000kg)
          Log.infoln("weight = %d", weight);
        } else if (enteredKey == '#') {  // exist setting mode
          configure.setMode(Mode_t::SCALE);
          lcd.setDisplayState(LCD_Display_State_t::Scale_Welcome);
          break;
        }
      }

      Setting_State_t curSettingState = configure.getSettingState();

      if (Setting_State_t::SETTING_OVERLOAD == curSettingState
          && '*' == enteredKey) {
        break;  // break while(configure.getCurrentMode() == Mode_t::SETTING)
      }

      // Update weight thresholds
      switch (curSettingState) {
        case Setting_State_t::SETTING_MOTOBIKE:
          configure.setMotoThreshold(weight);
          break;
        case Setting_State_t::SETTING_CAR:
          configure.setCarThreshold(weight);
          break;
      }

      configure.nextSettingState();
    }
  } else {  // Scale mode
    unsigned int weight = scale.getWeight();
    lcd.displayWeight(weight);
    // LED controll
  }


#else  // test mode
  // keypad.test();
  // scale.test();
#endif
}
