#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
class timer{
    private:
       unsigned long initialTime;
    public:
       timer(); //costruttore
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

       void printGameOverLCD(int score);
       void printNewPointLCD(int score);
       void printNotteLCD();
       void printWelcomeAndDifficultyLCD();
       void printGoLCD();
       void printDifficultyLCD(int difficulty);       
};

#endif
