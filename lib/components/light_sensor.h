#ifndef __LIGHT_SENSOR_H_INCLUDED
#define __LIGHT_SENSOR_H_INCLUDED

#include "lib.h"

namespace Components {
    class LightSensor {
    public:
        LightSensor(pin_t pin);

        float read() const;

    private:
        pin_t pin;
    };
}

#endif