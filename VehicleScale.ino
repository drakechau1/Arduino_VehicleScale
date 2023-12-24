#define DISABLE_LOGGING
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

  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);

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
    Log.infoln("SETTING MODE");

    configure.setMode(Mode_t::SETTING);
    configure.setSettingState(Setting_State_t::SETTING_MOTOBIKE);
    lcd.setDisplayState(LCD_Display_State_t::Setting_Motobike);
    lcd.setMode(LCD_Mode_t::Setting);
    // setting configure
    while (configure.getMode() == Mode_t::SETTING) {
      lcd.displaySetting();

      int weight = 0;
      char enteredKey = keypad.getKey();

      while (enteredKey != '*') {  // OK key
        enteredKey = keypad.getKey();

        // ascii: '0' -> 48, '9' -> 57
        if (enteredKey >= '0' && enteredKey <= '9') {
          weight = int(weight * 10 + (int)(enteredKey - 48));            // Concat chars to int
          weight = weight > MAX_SCALE_VALUE ? MAX_SCALE_VALUE : weight;  // Constrains value with max value is MAX_SCALE_VALUE (20000kg)
          Log.infoln("weight = %d", weight);
        } else if (enteredKey == '#') {  // exist setting mode
          configure.setMode(Mode_t::SCALE);
          lcd.setMode(LCD_Mode_t::Scale);
          break;
        }
      }

      Setting_State_t curSettingState = configure.getSettingState();

      if (Setting_State_t::SETTING_OVERLOAD == curSettingState
          && '*' == enteredKey) {
        lcd.setMode(LCD_Mode_t::Scale);
        configure.setMode(Mode_t::SCALE);
        break;  // break while(configure.getCurrentMode() == Mode_t::SETTING)
      }

      // Update weight thresholds
      switch (curSettingState) {
        case Setting_State_t::SETTING_MOTOBIKE:
          configure.setMotoThreshold(weight);
          lcd.setDisplayState(LCD_Display_State_t::Setting_Car);
          break;
        case Setting_State_t::SETTING_CAR:
          lcd.setDisplayState(LCD_Display_State_t::Setting_Overload);
          configure.setCarThreshold(weight);
          break;
      }

      configure.nextSettingState();
    }
  } else {  // Scale mode
            // Log.infoln("SCALE MODE");
    int weight = scale.getWeight();
    Log.infoln("Weight: %d", weight);
    lcd.displayWeight(weight);
    // LED controll
    if (weight > configure.getCarThreshold()) {
      digitalWrite(A0, HIGH);
      delay(500);
      digitalWrite(A0, LOW);
      delay(500);
      digitalWrite(A0, HIGH);
    } else {
      digitalWrite(A0, LOW);
    }
  }


#else  // test mode
  // keypad.test();
  // scale.test();
#endif
}
