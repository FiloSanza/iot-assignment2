#ifndef __LED_H_INCLUDED
#define __LED_H_INCLUDED

#include "lib.h"
#include "task.h"

namespace Components {
    /**
     * On/Off led.
     */
    class Led {
    public:
        Led();
        Led(pin_t pin);

        /**
         * Call this function to initialize the led.
         * Link the pin of the led to the pin mode.
         */
        void setUp();
        void turnOn();
        void turnOff();
        void switchState();
        
        bool isOn() const; 

    protected:
        pin_t pin;
        bool is_on = false;
    };
}

#endif
