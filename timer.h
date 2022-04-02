#ifndef __TIMER_H__
#define __TIMER_H__

class Timer{
   private:
      // Starting time for the timer
      unsigned long startTime;
   public:
      Timer(); // empty constructor
      // Sets starting time for this timer
      void startTimer();
      // Checks time out for this timer
      bool checkExpired(int t);
};

#endif