#ifndef __PIR_H_INCLUDED
#define __PIR_H_INCLUDED

#include "lib.h"

namespace Components {
  class Pir {
    public:
      Pir();
      Pir(uint8_t pin);

      bool read();

  private:
    uint8_t pin;
  };
}

#endif