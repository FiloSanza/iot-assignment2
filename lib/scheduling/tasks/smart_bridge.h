#ifndef _SMART_BRIDGE_H_INCLUDED
#define _SMART_BRIDGE_H_INCLUDED

#include "lcd.h"
#include "led.h"
#include "task.h"
#include "motor.h"
#include "sonar.h"
#include "types.h"
#include "button.h"
#include "blink_led.h"
#include "smart_bridge.h"
#include "potentiometer.h"

namespace Tasks {
    class SmartBridge : public Scheduling::PeriodicTask {
    public:
        SmartBridge() = default;
        SmartBridge(
            Components::LCD* lcd,
            Components::Led* led_a,
            Components::Led* led_b,
            Components::Led* led_c,
            Components::Motor* valve,
            Components::Sonar* sonar,
            Components::Button* button,
            Components::Potentiometer* pot,
            Tasks::BlinkLed* blink_led
        );

        void init();
        void tick();

    private:
        float water_level;
        BridgeState state;
        Components::LCD* lcd;
        Components::Led* led_a;
        Components::Led* led_b;
        Components::Led* led_c;
        Components::Motor* valve;
        Components::Sonar* sonar;
        Components::Button* button;
        Tasks::BlinkLed* blink_led;
        Components::Potentiometer* pot;
        LCDLine message[MESSAGE_LINES];

        void displayMessage();
        int computeValveAngle();
        BridgeState computeBridgeState();

        static const char* bridgeStateToString(BridgeState state);
        static const timestamp_t getBridgeStatePeriod(BridgeState state);
    };
}

#endif