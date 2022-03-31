#include "timer.h"

Timer::Timer() {
  
}
void Timer::startTimer() {
  initialTime = millis();
}
bool Timer::checkExpired(int t) {
  if(millis() - initialTime >= t) {
    return true;
  }
  return false;
}