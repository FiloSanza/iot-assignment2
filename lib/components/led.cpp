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
        : period(period), Led(pin) {}

    void BlinkingLed::update() {
        timestamp_t now = millis();
        if (now - previous_millis < period) {
            return;
        }

        previous_millis = now;
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