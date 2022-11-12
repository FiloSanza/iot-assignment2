#ifndef __SONAR_H_INCLUDED
#define __SONAR_H_INCLUDED

// #include <NewPing.h>
#include <Arduino.h>
#include "component.h"
#include "types.h"
#include "consts.h"

namespace Components {
    class Sonar : public ReadableComponent<float> {
    public:
        Sonar() = default;
        Sonar(pin_t echo_pin, pin_t trigger_pin);

        float read();
        float readAverage(uint32_t iterations);
    private:
        // NewPing sensor;
        pin_t echo_pin;
        pin_t trigger_pin;
    };
}

#endif