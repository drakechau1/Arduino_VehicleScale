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

Mode_t mode = Mode_t::SCALE;
int state = WELCOME;  // initialize state value

void turnOnLed() {
  digitalWrite(A0, HIGH);
  delay(200);
  digitalWrite(A0, LOW);
  delay(200);
  digitalWrite(A0, HIGH);
}

void turnOffLed() {
  digitalWrite(A0, LOW);
}

void settingMode() {
  mode = Mode_t::SETTING;
  state = MOTOBIKE;

  while (Mode_t::SETTING == mode) {
    lcd.setDisplayState(state);
    lcd.displaySetting();

    int weight = 0;
    char enteredKey = keypad.getKey();

    while ('*' != enteredKey) {
      enteredKey = keypad.getKey();
      // ascii: '0' -> 48, '9' -> 57
      if (enteredKey >= '0' && enteredKey <= '9' || enteredKey == 'D') {
        if (enteredKey == 'D') {
          weight = 0;
        } else {
          weight = int(weight * 10 + (int)(enteredKey - 48));            // Concat chars to int
          weight = weight > MAX_SCALE_VALUE ? MAX_SCALE_VALUE : weight;  // Constrains value with max value is MAX_SCALE_VALUE (20000kg)
        }

        lcd.setCursor(14, 3);
        lcd.print("     ");  // erases last value display
        lcd.setCursor(14, 3);
        lcd.print(weight);

        Log.infoln("new weight = %d", weight);
      } else if (enteredKey == '#') {  // exist setting mode
        mode = Mode_t::SCALE;
        return;  // exit setting mode
      }
    }

    if (OVERLOAD == state
        && '*' == enteredKey) {
      mode = Mode_t::SCALE;
      return;  // exit setting mode
    }

    // Update weight thresholds
    switch (state) {
      case MOTOBIKE:
        if (weight > 0)
          configure.setMotoThreshold(weight);
        state = CAR;
        break;
      case CAR:
        if (weight > 0)
          configure.setCarThreshold(weight);
        state = OVERLOAD;
        break;
    }
  }
}

void scaleMode() {
  int weight = scale.getWeight();
  Log.infoln("Weight: %d", weight);

  if (lcd.getDisplayState() != state) {
    // LED controll
    if (state != WELCOME && state != INIT) {
      turnOnLed();
    } else {
      turnOffLed();
    }
    // LCD controll
    lcd.clear();
    lcd.setDisplayState(state);
  }

  if (weight < LOWER_THRESHOLD_MOTO) {
    state = WELCOME;
    lcd.printScale_Welcome();
  } else if (weight < configure.getMotoThreshold()) {
    state = MOTOBIKE;
    lcd.printScale_Motobike(weight);
  } else if (weight < configure.getCarThreshold()) {
    state = CAR;
    lcd.printScale_Car(weight);
  } else {  // Overload
    state = OVERLOAD;
    lcd.printScale_Overload(weight);
  }
}

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

  // Setting mode
  if ('#' == settingKey) {
    settingMode();
  } else {
    scaleMode();
  }


#else  // test mode
  // keypad.test();
  // scale.test();
#endif
}
