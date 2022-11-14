#include "smart_bridge.h"
#include "logger.h"

namespace Tasks{
    SmartBridge::SmartBridge(
        Components::LCD* lcd,
        Components::Led* led_b,
        Components::Motor* valve,
        Components::Sonar* sonar,
        Components::Button* button,
        Components::Potentiometer* pot,
        Tasks::BlinkLed* blink_led,
        Tasks::SmartLight* smart_light
    ) : lcd(lcd),
        led_b(led_b),
        valve(valve),
        sonar(sonar),
        button(button),
        pot(pot),
        blink_led(blink_led),
        smart_light(smart_light) {
        setPeriodAndRestartTimer(PE_BEGIN);
        message[0].row = FIRST_LINE;
        message[0].column = FIRST_COLUMN;
        message[1].row = SECOND_LINE;
        message[1].column = FIRST_COLUMN;
    }

    void SmartBridge::init() {
        state = BridgeState::Begin;
    }

    void SmartBridge::tick() {
        if (!canRun()) {
            return;
        }

        BridgeState new_state = updateWaterLevelAndGetBridgeState();

        if (state == new_state) { 
            return;
        }
        state = new_state;

        Logger::Message msg;
        msg.setSource(DEFAULT_SMART_BRIDGE_TASK_NAME)
           .setLevel(Logger::LogLevel::Info)
           .setContent("new state: " + String(SmartBridge::bridgeStateToString(state)) + " | water level: " + String(water_level))
           .log();

        displayMessage();
        timestamp_t new_period = getBridgeStatePeriod(state);
        setPeriodAndRestartTimer(new_period);

        switch (state) {
        case BridgeState::Normal:   return set_normal_state();
        case BridgeState::PreAlarm: return set_pre_alarm_state();
        case BridgeState::Alarm:    return set_alarm_state();
        default:                    return;
        }        
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
            return pot->read();
        }
        return map(water_level, WATER_LEVEL_2, WATER_LEVEL_MAX, SERVO_LOWER_BOUND, SERVO_UPPER_BOUND);
    }    

    BridgeState SmartBridge::updateWaterLevelAndGetBridgeState() {
        water_level = sonar->readAverage(WATER_LEVEL_READS);
        if (water_level < WATER_LEVEL_1) {
            return BridgeState::Normal;
        } else if (water_level < WATER_LEVEL_2) {
            return BridgeState::PreAlarm;
        } else {
            return BridgeState::Alarm;
        }
    }

    void SmartBridge::set_normal_state() {
        // Enable smart light system
        smart_light->turnOn();
        led_b->turnOn();
        
        // Turn off alarm led 
        blink_led->turnOff();
        blink_led->disableAlwaysOn();
    }
    
    void SmartBridge::set_pre_alarm_state() {
        smart_light->turnOn();
        
        // Enable blinking of the alarm led
        blink_led->disableAlwaysOn();
        blink_led->turnOn();
    }
    
    void SmartBridge::set_alarm_state() {
        // Disable smart light system
        smart_light->turnOff();
        led_b->turnOff();
        
        // Disable blinking alarm led, set it to always on 
        blink_led->turnOn();
        blink_led->enableAlwaysOn();

        valve->moveTo(computeValveAngle());
    }

    const char* SmartBridge::bridgeStateToString(BridgeState state) {
        switch (state) {
            case BridgeState::Normal:   return "NORMAL";
            case BridgeState::PreAlarm: return "PREALARM";
            case BridgeState::Alarm:    return "ALARM";
            default:                    return "UNKNOWN_BRIDGE_STATE";
        }
    }

    const timestamp_t SmartBridge::getBridgeStatePeriod(BridgeState state) {
        switch (state) {
            case BridgeState::Normal:   return PE_NORMAL;
            case BridgeState::PreAlarm: return PE_PREALARM;
            case BridgeState::Alarm:    return PE_ALARM;
            default:                    return PE_BEGIN;
        }
    }
}