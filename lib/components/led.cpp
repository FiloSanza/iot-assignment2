#include "lib.h"
#include "led.h"

namespace Components {
  Led::Led() {}

  Led::Led(uint8_t pin) : pin(pin) {}

  void Led::setUp() {
    pinMode(pin, OUTPUT);
  }

  void Led::turnOn() {
    if (!is_on) {
      is_on = true;
      digitalWrite(pin, HIGH);
    }
  }

  void Led::turnOff() {
    if (is_on) {
      is_on = false;
      digitalWrite(pin, LOW);
    }
  }

  BlinkingLed::BlinkingLed() {}

  BlinkingLed::BlinkingLed(uint8_t pin, uint16_t period)
      : period(period), Led(pin) {
  }

  void BlinkingLed::update() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= period) {
      previousMillis = currentMillis;
      if (!is_on) {
          turnOn();
      } else {
        turnOff();
      }
    }
  }


}