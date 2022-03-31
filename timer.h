#ifndef __TIMER_H__
#define __TIMER_H__

class Timer{
    private:
       unsigned long initialTime;
    public:
       Timer(); //constructor
       void startTimer();
       bool checkExpired(int t);
};

#endif