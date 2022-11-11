#ifndef __SONAR_H_INCLUDED
#define __SONAR_H_INCLUDED

#include <NewPing.h>
#include "lib.h"
#include "component.h"

namespace Components {
    class Sonar : public ReadableComponent<float> {
    public:
        Sonar() = default;
        Sonar(pin_t echo_pin, pin_t trigger_pin, uint32_t max_distance = MAX_SENSOR_DISTANCE);

        float read();
        float readAverage(uint32_t iterations);
    private:
        NewPing sensor;
    };
}

#endif