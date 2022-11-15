#include <Arduino.h>

#include <components.h>
#include <scheduling.h>
#include <utils.h>
#include <consts.h>

Components::LCD* lcd;
Components::Led* smart_led;
Components::Led* bridge_open_led;
Components::Led* warning_led;
Components::Button* btn;
Components::Pir* pir;
Components::LightSensor* light_sensor;
Components::Sonar* sonar;
Components::Motor* valve;
Components::Potentiometer* pot;

Tasks::BlinkLed* blink_led;
Tasks::SmartLight* smart_light;
Tasks::SmartBridge* smart_bridge;

Scheduling::Scheduler* scheduler = new Scheduling::Scheduler();

void setup() {
    Serial.begin(9600);

    lcd = new Components::LCD(DEFAULT_LCD_ROWS, DEFAULT_LCD_COLUMNS, LCD_I2C_ADDRESS);
    smart_led = new Components::Led(SMART_LED_PIN);
    bridge_open_led = new Components::Led(BRIDGE_OPEN_LED_PIN);
    warning_led = new Components::Led(WARNING_LED_PIN);
    btn = new Components::Button(BUTTON_PIN);
    pir = new Components::Pir(PIR_PIN);
    valve = new Components::Motor(SERVO_PIN);
    light_sensor = new Components::LightSensor(LIGHT_SENSOR_PIN);
    sonar = new Components::Sonar(SONAR_ECHO_PIN, SONAR_TRIGGER_PIN);
    pot = new Components::Potentiometer(POT_PIN, 0, 180);

    smart_light = new Tasks::SmartLight(smart_led, light_sensor, pir, 1000);
    blink_led = new Tasks::BlinkLed(warning_led, BLINKING_PERIOD);
    smart_bridge = new Tasks::SmartBridge(
        lcd,
        valve,
        sonar,
        btn,
        blink_led,
        smart_light,
        pot,
        bridge_open_led
    );

    smart_bridge->init();

    scheduler->schedule(smart_light);
    scheduler->schedule(smart_bridge);
    scheduler->schedule(blink_led);

    Logger::Logger::getInstance().setLevel(Logger::LogLevel::Debug);
}

void loop() {
    scheduler->tick();
}