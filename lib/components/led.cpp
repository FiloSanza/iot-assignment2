#include "lib.h"
#include "led.h"

namespace Components
{
    Led::Led() {}
    Led::Led(pin_t pin) : pin(pin) {}

    void Led::setUp() {
        pinMode(pin, OUTPUT);
    }

    void Led::turnOn() {
        if (!is_on) {
            is_on = true;
            digitalWrite(pin, HIGH);
        }
    }

    void Led::turnOff() {
        if (is_on) {
            is_on = false;
            digitalWrite(pin, LOW);
        }
    }

    BlinkingLed::BlinkingLed() {}
    BlinkingLed::BlinkingLed(pin_t pin, timestamp_t period)
        : pin(pin) {
        pinMode(pin, OUTPUT);
    }

    void BlinkingLed::init() {
        turnOff();
    }

    void BlinkingLed::tick() {
        if (!canRun()) {
            return;
        }

        last_execution = millis();
        switchState();
    }

    void BlinkingLed::switchState() {
        if (is_on) {
            turnOff();
        }
        else {
            turnOn();
        }
    }
}