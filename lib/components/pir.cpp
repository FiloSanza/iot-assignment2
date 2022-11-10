#include "lib.h"
#include "pir.h"

namespace Components {
  Pir::Pir() {}

  Pir::Pir(pin_t pin) : pin(pin) {}

  bool Pir::read() {
    return digitalRead(pin) == HIGH;
  }
}