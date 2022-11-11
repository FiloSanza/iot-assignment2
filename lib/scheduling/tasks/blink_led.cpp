#include "blink_led.h"

namespace Tasks {
    BlinkLed::BlinkLed(Components::Led* led, timestamp_t period) : led(led) {
        setPeriodAndRestartTimer(period);
    }

    void BlinkLed::init() {}

    void BlinkLed::tick() {
        if (!canRun()) {
            return;
        }

        Serial.flush();

        led->switchState();
        markExecutedNow();
    }
}