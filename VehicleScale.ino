// #define DISABLE_LOGGING
// #define ENABLE_TEST
#include "ArduinoLog.h"
#include "Configuration.h"
#include "Custom_LCD.h"
#include "Custom_HX711.h"
#include "Custom_Keypad.h"

#define G2KG 1;  // đổi tỉ lệ: 1g = 1kg

Custom_LCD lcd(0x27, 20, 4);
Custom_HX711 scale;
Custom_Keypad keypad;
Configuration configure;

void turnLedOn() {
  digitalWrite(A0, HIGH);
  if (lcd.getDisplayState() == OVERLOAD) { // nếu quả tải nhấp nhấy led cảnh báo
    delay(200);
    digitalWrite(A0, LOW);
    delay(200);
    digitalWrite(A0, HIGH);
  }
}

void turnLedOff() {
  digitalWrite(A0, LOW);
}

void settingMode() {
  lcd.setDisplayState(MOTOBIKE);
  while (true) {
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
        return;
      }
    }

    if (lcd.getDisplayState() == OVERLOAD && '*' == enteredKey) {
      return;  // exit setting mode
    }

    // Update weight thresholds
    switch (lcd.getDisplayState()) {
      case MOTOBIKE:
        if (weight > 0)
          configure.setMotoThreshold(weight);
        lcd.setDisplayState(CAR);
        break;
      case CAR:
        if (weight > 0)
          configure.setCarThreshold(weight);
        lcd.setDisplayState(OVERLOAD);
        break;
    }
  }
}

void scaleMode() {
  int weight = scale.getWeight() * G2KG;
  Log.infoln("Weight: %d", weight);

  if (weight > LOWER_THRESHOLD_MOTO) {
    turnLedOn();
  } else {
    turnLedOff();
  }

  if (weight < LOWER_THRESHOLD_MOTO) {
    lcd.setDisplayState(WELCOME);
    lcd.printScale_Welcome();
  } else if (weight < configure.getMotoThreshold()) {
    lcd.setDisplayState(MOTOBIKE);
    lcd.printScale_Motobike(weight);
  } else if (weight < configure.getCarThreshold()) {
    lcd.setDisplayState(CAR);
    lcd.printScale_Car(weight);
  } else {  // Overload
    lcd.setDisplayState(OVERLOAD);
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

  // lcd.setDisplayState(WELCOME);

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
