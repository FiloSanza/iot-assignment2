#ifndef _BLINK_LED_INCLUDED
#define _BLINK_LED_INCLUDED

#include "task.h"
#include "led.h"

namespace Tasks {
    
    class BlinkLed : public Scheduling::PeriodicTask {
    public:
        BlinkLed() = default;
        BlinkLed(Components::Led* led, timestamp_t period);

        void init();
        void tick();

        /**
         * The task is still enabled but we want to keep the light off.
         */
        void turnOff();
        /**
         * The led will start blinking again.
         */
        void turnOn();
        /**
         * Set always on, the led will be on all the time.
         */
        void enableAlwaysOn();
        /**
         * Disable always on mode, the led will start blinking.
         */
        void disableAlwaysOn();
    private:
        bool force_off;
        bool always_on;
        Components::Led* led;
    };
}

#endif