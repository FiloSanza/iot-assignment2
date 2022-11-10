#ifndef __LED_H_INCLUDED
#define __LED_H_INCLUDED

#include "lib.h"

namespace Components {
  /**
   * On/Off led.
   */
  class Led {
  public:
    Led();
    Led(uint8_t pin);

    /**
     * Call this function to initialize the led.
     * Link the pin of the led to the pin mode.
     */
    void setUp();
    void turnOn();
    void turnOff();

  protected:
    uint8_t pin;
    bool is_on = false;
  };

  /**
   * Fading led. It extends the Led class.
   */
  class FadingLed : public Led {
  public:
    FadingLed();
    FadingLed(uint8_t pin, uint16_t period);

    /**
     * Call this function to make the led pulsing.
     */
    void pulse();
  private:
    uint16_t period;
  };
}

#endif
