#include "timer.h"

Timer::Timer() {
  
}
void Timer::startTimer() {
  startTime = millis();
}
bool Timer::checkExpired(int t) {
  if(millis() - startTime >= t) {
    return true;
  }
  return false;
}