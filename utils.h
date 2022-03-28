#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
class timer{
    private:
       unsigned long initialTime;
    public:
       timer(); //constructor
       void startTimer();
       bool checkExpired(int t);
};

class output {
   public:
       output();
       void printGameOver(int score);
       void printNewPoint(int score);
       void printNotte();
       void printWelcomeAndDifficulty();
       void printGo();
       void printDifficulty(int difficulty);
       
};

#endif
