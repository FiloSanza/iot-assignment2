#ifndef __SERVO_H_INCLUDED
#define __SERVO_H_INCLUDED

#include <Servo.h>
#include <Arduino.h>
#include "types.h"

namespace Components {
    class Motor {
    public:
        Motor();
        Motor(pin_t pin);
        ~Motor();

        void moveTo(int angle);
    private:
        Servo servo;
    };
}

#endif