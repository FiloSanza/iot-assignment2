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
    Led(pin_t pin);

    /**
     * Call this function to initialize the led.
     * Link the pin of the led to the pin mode.
     */
    void setUp();
    virtual void turnOn();
    virtual void turnOff();

  protected:
    pin_t pin;
    bool is_on = false;
  };

  /**
   * Blinking led. It extends the Led class.
   */
  class BlinkingLed : public Led {
  public:
    BlinkingLed();
    BlinkingLed(pin_t pin, uint16_t period);

    void update();
  private:
    uint16_t period;
    unsigned long previousMillis = 0; 
  };
}

#endif
