#ifndef _ENUMS_H_INCLUDED
#define _ENUMS_H_INCLUDED

#include <cstdint>

typedef uint8_t pin_t;
typedef unsigned long timestamp_t;

struct LCDLine {
    String text;
    uint32_t row;
    uint32_t column;
};

enum class ButtonState {
    Pressed,
    NotPressed 
};

#endif