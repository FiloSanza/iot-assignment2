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

    /**
     * The task is still enabled but we want to keep the light off.
     */
    void BlinkLed::turnOff() {
        force_off = true;
        always_on = false;
    }

    /**
     * The led will start blinking again.
     */
    void BlinkLed::turnOn() {
        force_off = false;
    }

    /**
     * Set always on, the led will be on all the time.
     */
    void BlinkLed::enableAlwaysOn() {
        always_on = true;
        force_off = false;
    }

    /**
     * Disable always on mode, the led will start blinking.
     */
    void BlinkLed::disableAlwaysOn() {
        always_on = false;
    }

}