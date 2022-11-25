#include "smart_bridge.h"
#include "logger.h"

namespace Tasks{
    SmartBridge::SmartBridge(
        Components::LCD* lcd,
        Components::Motor* valve,
        Components::Sonar* sonar,
        Components::Button* button,
        Tasks::BlinkLed* blink_led,
        Tasks::SmartLight* smart_light,
        Components::Potentiometer* pot,
        Components::Led* bridge_open_led
    ) : lcd(lcd),
        valve(valve),
        sonar(sonar),
        button(button),
        blink_led(blink_led),
        smart_light(smart_light),
        pot(pot),
        bridge_open_led(bridge_open_led),
        last_valve_override(0),
        valve_override(0) {
        setPeriodAndRestartTimer(PE_NORMAL);
        message[0].row = FIRST_LINE;
        message[0].column = FIRST_COLUMN;
        message[1].row = SECOND_LINE;
        message[1].column = FIRST_COLUMN;
    }

    void SmartBridge::init() {
        state = BridgeState::Normal;
        valve->moveTo(0);
    }

    void SmartBridge::tick() {
        if (!canRun()) {
            return;
        }

        markExecutedNow();

        BridgeState new_state = updateWaterLevelAndGetBridgeState();

        Logger::Message msg;
        msg.setSource(TaskId::SmartBridge)
           .setLevel(Logger::LogLevel::Info)
           .setData(String(water_level))
           .setTag(SmartBridgeMessageTag::WaterLevelUpdate)
           .setDescription("water level update")
           .log();

        if (new_state == BridgeState::Alarm) {
            valve->moveTo(computeValveAngle());
        }

        if (state == new_state) { 
            // Display new water level only
            displayMessage();
            return;
        }
        // Display new water level and state
        state = new_state;
        displayMessage();

        msg.setSource(TaskId::SmartBridge)
           .setLevel(Logger::LogLevel::Info)
           .setData(String(state))
           .setTag(SmartBridgeMessageTag::NewStateUpdate)
           .setDescription("new state")
           .log();

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
        lcd->clear();
        const char* bridge_state = SmartBridge::bridgeStateToString(state);
        message[0].text = "State: " + String(bridge_state);
        message[1].text = "WL: " + String(water_level);
        if (state == BridgeState::Alarm) {
            message[1].text += " VO: " + String(valve->read());
        }
        lcd->displayMessage(message, MESSAGE_LINES);
    }

    int SmartBridge::computeValveAngle() {
        if (button->read() == ButtonState::Pressed) {
            return pot->read();
        }

        if (Serial.available() > 0) {
            int byte_read;
            do {
                byte_read = Serial.read();
            } while (byte_read == 0 || Serial.available() > 0);
            if (byte_read >= 0 && byte_read <= 180) {
                valve_override = byte_read;
                last_valve_override = millis();
                return valve_override;
            }
        }

        if (millis() - last_valve_override < VALVE_OVERRIDE_DELTA) {
            return valve_override;
        }

        return map(WATER_LEVEL_2 - water_level + WATER_LEVEL_MIN, WATER_LEVEL_MIN, WATER_LEVEL_2, SERVO_LOWER_BOUND, SERVO_UPPER_BOUND);
    }    

    BridgeState SmartBridge::updateWaterLevelAndGetBridgeState() {
        water_level = sonar->read();
        if (water_level > WATER_LEVEL_1) {
            return BridgeState::Normal;
        } else if (water_level > WATER_LEVEL_2) {
            return BridgeState::PreAlarm;
        } else {
            return BridgeState::Alarm;
        }
    }

    void SmartBridge::set_normal_state() {
        // Enable smart light system
        smart_light->turnOn();
        bridge_open_led->turnOn();
        
        // Turn off alarm led 
        blink_led->turnOff();
        blink_led->disableAlwaysOn();

        valve->moveTo(0);
    }

    void SmartBridge::set_pre_alarm_state() {
        smart_light->turnOn();
        bridge_open_led->turnOn();
        
        // Enable blinking of the alarm led
        blink_led->disableAlwaysOn();
        blink_led->turnOn();

        valve->moveTo(0);
    }
    
    void SmartBridge::set_alarm_state() {
        // Disable smart light system
        smart_light->turnOff();
        bridge_open_led->turnOff();
        
        // Disable blinking alarm led, set it to always on 
        blink_led->turnOn();
        blink_led->enableAlwaysOn();
    }

    const char* SmartBridge::bridgeStateToString(BridgeState state) {
        switch (state) {
            case BridgeState::Normal:   return "NORMAL";
            case BridgeState::PreAlarm: return "WARN";
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