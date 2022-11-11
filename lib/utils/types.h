#ifndef _ENUMS_H_INCLUDED
#define _ENUMS_H_INCLUDED

#include <inttypes.h>
#include <Arduino.h>
#include "component.h"

typedef uint8_t pin_t;
typedef unsigned long timestamp_t;

struct LCDLine {
    String text;
    uint32_t row;
    uint32_t column;
};

enum ButtonState {
    NotPressed = 0,
    Pressed = 1
};

#endif