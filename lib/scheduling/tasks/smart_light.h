#ifndef _SMART_LIGH_H_INCLUDED
#define _SMART_LIGH_H_INCLUDED

#include "task.h"
#include "pir.h"
#include "led.h"
#include "light_sensor.h"

namespace Tasks {
    class SmartLight : public Scheduling::PeriodicTask {
    public:
        SmartLight() = default;
        SmartLight(
            Components::Led* led, 
            Components::LightSensor* light_sensor, 
            Components::Pir* pir, 
            timestamp_t period
        );

        void init();
        void tick();
        /**
         * The task is still enabled but we want to keep the light off
         * ignoring the PIR and the light sensor.
         */
        void turnOff();
        /**
         * The task is still enabled we now want to control the led using
         * the sensors.
         */
        void turnOn();
        
    private:
        bool force_off;
        Components::Led* led;
        Components::LightSensor* light_sensor;
        Components::Pir* pir;
    };
}

#endif