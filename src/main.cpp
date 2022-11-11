#include <Arduino.h>

#include <components.h>
#include <scheduling.h>
#include <utils.h>

#define LED_PIN             4
#define BTN_PIN             2
#define PIR_PIN             12
#define SONAR_ECHO_PIN      7
#define SONAR_TRIGGER_PIN   8
#define LIGHT_SENSOR_PIN    A1
#define POT_PIN             A0

Components::Led* led;
Components::Button* btn;
Components::Pir* pir;
Components::LightSensor* light_sensor;
// Components::Sonar* sonar;
Components::Potentiometer* pot;

Tasks::BlinkLed* blink;
Tasks::PrintDebug<bool>* print_bool = new Tasks::PrintDebug<bool>(100);
Tasks::PrintDebug<float>* print_float = new Tasks::PrintDebug<float>(10000);
Tasks::PrintDebug<uint16_t>* print_uint = new Tasks::PrintDebug<uint16_t>(10000);
Tasks::PrintDebug<ButtonState>* print_btn = new Tasks::PrintDebug<ButtonState>(10000);

Scheduling::Scheduler* scheduler = new Scheduling::Scheduler();

void setup() {
    Serial.begin(9600);
    
    led = new Components::Led(LED_PIN);
    btn = new Components::Button(BTN_PIN);
    pir = new Components::Pir(PIR_PIN);
    light_sensor = new Components::LightSensor(LIGHT_SENSOR_PIN);
    // // sonar = new Components::Sonar(SONAR_ECHO_PIN, SONAR_TRIGGER_PIN);
    pot = new Components::Potentiometer(POT_PIN, 0, 180);

    blink = new Tasks::BlinkLed(led, 1000);

    scheduler->schedule(blink);
    scheduler->schedule(print_btn);
    scheduler->schedule(print_bool);
    scheduler->schedule(print_uint);
    scheduler->schedule(print_float);

    print_bool->addComponent("PIR", pir);
    print_btn->addComponent("Bottone", btn);
    print_uint->addComponent("Potenziometro", pot);
    print_float->addComponent("Luce", light_sensor);

    Logger::Logger::getInstance().setLevel(Logger::LogLevel::Debug);
}

void loop() {
    scheduler->tick();
}