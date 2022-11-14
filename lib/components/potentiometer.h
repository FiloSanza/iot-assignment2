#ifndef __POTENTIOMETER_H_INCLUDED
#define __POTENTIOMETER_H_INCLUDED

#include "component.h"
#include <Arduino.h>
#include "types.h"

namespace Components {
    class Potentiometer : public ReadableComponent<uint32_t> {
    public:
        Potentiometer(pin_t pin, uint32_t lower_bound, uint32_t upper_bound);

        void setUpperBound(uint32_t value);
        void setLowerBound(uint32_t value);

        uint32_t getUpperBound() const;
        uint32_t getLowerBound() const;
        uint32_t read();

    private:
        pin_t pin;
        uint32_t lower_bound;
        uint32_t upper_bound;
    };
}

#endif