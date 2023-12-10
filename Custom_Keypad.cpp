#include "Custom_Keypad.h"

void Custom_Keypad::test() {
  char key = getKey();

  if (key) {
    Log.infoln("Pressed key: %c", key);
  }
}