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
#include "smart_light.h"
#include "potentiometer.h"

namespace Tasks {
    class SmartBridge : public Scheduling::PeriodicTask {
    public:
        SmartBridge() = default;
        SmartBridge(
            Components::LCD* lcd,
            Components::Led* led_b,
            Components::Motor* valve,
            Components::Sonar* sonar,
            Components::Button* button,
            Components::Potentiometer* pot,
            Tasks::BlinkLed* blink_led,
            Tasks::SmartLight* smart_light
        );

        void init();
        void tick();

    private:
        int water_level;
        BridgeState state;
        Components::LCD* lcd;
        Components::Led* led_b;
        Components::Led* led_c;
        Components::Motor* valve;
        Components::Sonar* sonar;
        Components::Button* button;
        Components::Potentiometer* pot;
        Tasks::BlinkLed* blink_led;
        Tasks::SmartLight* smart_light;
        LCDLine message[MESSAGE_LINES];

        void set_normal_state();
        void set_pre_alarm_state();
        void set_alarm_state();
        void displayMessage();
        int computeValveAngle();
        BridgeState updateWaterLevelAndGetBridgeState();

        static const char* bridgeStateToString(BridgeState state);
        static const timestamp_t getBridgeStatePeriod(BridgeState state);
    };
}

#endif