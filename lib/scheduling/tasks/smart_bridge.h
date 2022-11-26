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
            Components::Motor* valve,
            Components::Sonar* sonar,
            Components::Button* button,
            Tasks::BlinkLed* blink_led,
            Tasks::SmartLight* smart_light,
            Components::Potentiometer* pot,
            Components::Led* bridge_open_led
        );

        void init();
        void tick();

    private:
        int water_level;
        bool button_pressed;
        BridgeState state;
        Components::LCD* lcd;
        Components::Led* led_c;
        Components::Motor* valve;
        Components::Sonar* sonar;
        Components::Button* button;
        Tasks::BlinkLed* blink_led;
        Tasks::SmartLight* smart_light;
        Components::Potentiometer* pot;
        Components::Led* bridge_open_led;
        LCDLine message[MESSAGE_LINES];
        timestamp_t last_valve_override;
        timestamp_t last_button_pressed;
        int valve_override;

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