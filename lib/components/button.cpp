#include "button.h"
#include "consts.h"

namespace Components {
    Button::Button(pin_t pin, bool use_pullup_resistor) 
        : pin(pin), last_press(0), state(ButtonState::NotPressed) {
        uint8_t pin_mode = use_pullup_resistor 
            ? INPUT_PULLUP 
            : INPUT;
        
        pinMode(pin, pin_mode);
    }

    ButtonState Button::read() {
        timestamp_t now = millis();
        if (isBouncing(now)) {
            return state;
        }

        last_press = now;
        state = digitalRead(pin) == HIGH
            ? ButtonState::Pressed
            : ButtonState::NotPressed;
        
        return state;
    }

    bool Button::isBouncing(timestamp_t now) {
        return (now - last_press) < BUTTON_BOUNCING_DELAY;
    }
}