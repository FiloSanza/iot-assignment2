#ifndef __BUTTON_H_INCLUDED
#define __BUTTON_H_INCLUDED

#include <Arduino.h>
#include "component.h"
#include "types.h"

namespace Components {
    class Button : public ReadableComponent<ButtonState> {
    public:
        Button(pin_t pin, bool use_pullup_resistor = true);

        ButtonState read();
    private:
        bool isBouncing(timestamp_t now);

        pin_t pin;
        timestamp_t last_press;
        /**
        * Lazily evaluated by read.
        * There is no need to do polling, the value will be updated accordingly
        * when a read is performed.
        */
        ButtonState state;
        bool use_pullup_resistor;
        
    };
}

#endif