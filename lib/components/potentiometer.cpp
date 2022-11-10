#include "potentiometer.h"

namespace Components {

    Potentiometer::Potentiometer(pin_t pin, uint16_t lower_bound, uint16_t upper_bound) 
        : pin(pin), lower_bound(lower_bound), upper_bound(upper_bound) {}

    void Potentiometer::setUpperBound(uint16_t value) {
        upper_bound = value;
    }

    void Potentiometer::setLowerBound(uint16_t value) {
        lower_bound = value;
    }

    uint16_t Potentiometer::getUpperBound() const {
        return upper_bound;
    }

    uint16_t Potentiometer::getLowerBound() const {
        return lower_bound;
    }

    uint16_t Potentiometer::read() const {
        int sensor_value = analogRead(pin);
        return map(sensor_value, 0, 1023, lower_bound, upper_bound);
    }

}