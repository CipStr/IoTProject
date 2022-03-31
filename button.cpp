#include "button.h"

bool Button::isCurrentlyPressed() {
    return digitalRead(this->pin) == HIGH;
}