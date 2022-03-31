#include "led.h"

RedLed::RedLed(int p) {
    pin = p;
    fadeAmount = 5;
    intensity = 0;
}

void RedLed::updateIntensity() {
    if((intensity >= 255 && fadeAmount > 0) || (intensity <= 0 && fadeAmount <0)) {
        fadeAmount = -fadeAmount;
    }
    intensity += fadeAmount;
    analogWrite(this->pin, intensity);
}