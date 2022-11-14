#include "blink_led.h"
#include "components.h"
#include "smart_bridge.h"

namespace Tasks{
    SmartBridge::SmartBridge(
        Components::LCD* lcd,
        Components::Led* led_a,
        Components::Led* led_b,
        Components::Led* led_c,
        Components::Motor* valve,
        Components::Sonar* sonar,
        Components::Button* button,
        Components::Potentiometer* pot,
        Tasks::BlinkLed* blink_led
    ) : lcd(lcd),
        led_a(led_a),
        led_b(led_b),
        led_c(led_c),
        valve(valve),
        sonar(sonar),
        button(button),
        pot(pot),
        blink_led(blink_led) {
            setPeriodAndRestartTimer(PE_BEGIN);
        }

    void SmartBridge::init() {
        message[0].row = FIRST_LINE;
        message[0].column = FIRST_COLUMN;
        message[1].row = SECOND_LINE;
        message[1].column = FIRST_COLUMN;
        state = BridgeState::Begin;
    }

    void SmartBridge::tick() {
        if (!canRun()) {
            return;
        }
        const BridgeState new_state = computeBridgeState();
        displayMessage();
        if (new_state == state) {
            return;
        }
        state = new_state;
        switch (state) {
        case BridgeState::Normal:
            led_a->turnOff();
            led_b->turnOn();
            led_c->turnOff();
            break;
        case BridgeState::PreAlarm:
            led_a->turnOff();
            blink_led->enable();
            led_c->turnOff();
            break;
        case BridgeState::Alarm:
            led_a->turnOff();
            led_b->turnOff();
            led_c->turnOn();
            valve->moveTo(computeValveAngle());
            break;
        default:
            break;
        }
        setPeriodAndRestartTimer(getBridgeStatePeriod(state));
    }

    void SmartBridge::displayMessage() {
        const char* bridge_state = SmartBridge::bridgeStateToString(state);
        message[0].text = "State: " + String(bridge_state);
        message[1].text = "WL: " + String(water_level);
        if (state == BridgeState::Alarm) {
            message[1].text += ", VO: " + String(valve->read());
        }
        lcd->displayMessage(message, MESSAGE_LINES);
    }

    int SmartBridge::computeValveAngle() {
        if (button->read() == ButtonState::Pressed) {
            return map(
                pot->read(),
                pot->getLowerBound(), 
                pot->getUpperBound(),
                SERVO_LOWER_BOUND,
                SERVO_UPPER_BOUND
            );
        }
        return map(
            water_level,
            WATER_LEVEL_1,
            WATER_LEVEL_MAX,
            SERVO_LOWER_BOUND,
            SERVO_UPPER_BOUND
        );
    }    

    BridgeState SmartBridge::computeBridgeState() {
        water_level = sonar->read();
        if (water_level < WATER_LEVEL_1) {
            return BridgeState::Normal;
        } else if (water_level < WATER_LEVEL_2) {
            return BridgeState::PreAlarm;
        } else {
            return BridgeState::Alarm;
        }
    }

    const char* SmartBridge::bridgeStateToString(BridgeState state) {
        switch (state) {
            case BridgeState::Normal: return "NORMAL";
            case BridgeState::PreAlarm:  return "PREALARM";
            case BridgeState::Alarm: return "ALARM";
            default:  return "UNKNOWN_BRIDGE_STATE";
        }
    }

    const timestamp_t SmartBridge::getBridgeStatePeriod(BridgeState state) {
        switch (state) {
            case BridgeState::Normal: return PE_NORMAL;
            case BridgeState::PreAlarm:  return PE_PREALARM;
            case BridgeState::Alarm: return PE_ALARM;
            default:  return PE_BEGIN;
        }
    }
}