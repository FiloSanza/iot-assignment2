#ifndef __POTENTIOMETER_H_INCLUDED
#define __POTENTIOMETER_H_INCLUDED

#include "lib.h"

namespace Components {
    class Potentiometer {
    public:
        Potentiometer(uint8_t pin, uint16_t lower_bound, uint16_t upper_bound);

        void setUpperBound(uint16_t value);
        void setLowerBound(uint16_t value);

        uint16_t getUpperBound() const;
        uint16_t getLowerBound() const;
        uint16_t read() const;

    private:
        uint8_t pin;
        uint16_t lower_bound;
        uint16_t upper_bound;
    };
}

#endif