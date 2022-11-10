#include "lib.h"
#include "led.h"

namespace Components {
  Led::Led() {}

  Led::Led(pin_t pin) : pin(pin) {}

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

  FadingLed::FadingLed() {}

  FadingLed::FadingLed(pin_t pin, uint16_t period)
      : period(period), Led(pin) {
  }

  void FadingLed::pulse() {
    if (is_on) { // Before start the pulsing it's necessary to turn on the led.

      // Instead of use the delay function (which is blocking) we use
      // millis function and cosine. Since cosine varies from -1 to 1
      // then we map the value obtained to the range [0, 255].
      pin_t value = 128 + 127 * cos(2 * PI / period * millis());
      analogWrite(pin, value);
    }
  }
}