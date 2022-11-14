#include "potentiometer.h"

namespace Components {

    Potentiometer::Potentiometer(pin_t pin, uint32_t lower_bound, uint32_t upper_bound) 
        : pin(pin), lower_bound(lower_bound), upper_bound(upper_bound) {}

    void Potentiometer::setUpperBound(uint32_t value) {
        upper_bound = value;
    }

    void Potentiometer::setLowerBound(uint32_t value) {
        lower_bound = value;
    }

    uint32_t Potentiometer::getUpperBound() const {
        return upper_bound;
    }

    uint32_t Potentiometer::getLowerBound() const {
        return lower_bound;
    }

    uint32_t Potentiometer::read() {
        int sensor_value = analogRead(pin);
        return map(sensor_value, 0, 1023, lower_bound, upper_bound);
    }

}