#include <Arduino.h>

#include <components.h>
#include <scheduling.h>
#include <utils.h>

Components::LCD* lcd;
Components::Led* led_a;
Components::Led* led_b;
Components::Led* led_c;
Components::Button* btn;
Components::Pir* pir;
Components::LightSensor* light_sensor;
Components::Sonar* sonar;
Components::Potentiometer* pot;

Tasks::SmartLight* smart_light;
Tasks::PrintDebug<bool>* print_bool = new Tasks::PrintDebug<bool>(10000);
Tasks::PrintDebug<float>* print_float = new Tasks::PrintDebug<float>(100);
Tasks::PrintDebug<uint16_t>* print_uint = new Tasks::PrintDebug<uint16_t>(10000);
Tasks::PrintDebug<ButtonState>* print_btn = new Tasks::PrintDebug<ButtonState>(10000);

Scheduling::Scheduler* scheduler = new Scheduling::Scheduler();

void setup() {
    Serial.begin(9600);
    
    // lcd = new Components::LCD(2, 16, 0x27);
    // led_a = new Components::Led(LED_PIN);
    // btn = new Components::Button(BTN_PIN);
    // pir = new Components::Pir(PIR_PIN);
    // light_sensor = new Components::LightSensor(LIGHT_SENSOR_PIN);
    // sonar = new Components::Sonar(SONAR_ECHO_PIN, SONAR_TRIGGER_PIN);
    // pot = new Components::Potentiometer(POT_PIN, 0, 180);

    // smart_light = new Tasks::SmartLight(led, light_sensor, pir, 10);

    scheduler->schedule(print_float);
    scheduler->schedule(smart_light);

    print_float->addComponent("Sonar", sonar);

    Logger::Logger::getInstance().setLevel(Logger::LogLevel::Info);
}

void loop() {
    scheduler->tick();
}