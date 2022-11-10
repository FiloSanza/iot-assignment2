#include "lib.h"
#include "pir.h"

namespace Components {
  Pir::Pir() {}

  Pir::Pir(uint8_t pin) : pin(pin) {}

  bool Pir::read() {
    return digitalRead(pin) == HIGH;
  }
}