#ifndef __LIGHT_SENSOR_H_INCLUDED
#define __LIGHT_SENSOR_H_INCLUDED

#include "lib.h"

namespace Components {
    class LightSensor {
    public:
        LightSensor(uint8_t pin);

        float read() const;

    private:
        uint8_t pin;
    };
}

#endif