#ifndef __PIR_H_INCLUDED
#define __PIR_H_INCLUDED

#include "lib.h"

namespace Components {
  class Pir {
    public:
      Pir();
      Pir(pin_t pin);

      bool read();

  private:
    pin_t pin;
  };
}

#endif