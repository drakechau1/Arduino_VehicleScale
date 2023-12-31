#pragma once

// the minimun of motobike threshold
#define LOWER_THRESHOLD_MOTO 20  // unit

#define MAX_SCALE_VALUE 20000  // kg

enum class Mode_t {
  SCALE,
  SETTING
};

enum State_t {
  INIT,
  WELCOME,
  MOTOBIKE,
  CAR,
  OVERLOAD
};

enum class Func_Key_t {
  SETTING = '#',
  SAVE = '*'
};