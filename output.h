#ifndef __UTILS_H__
#define __UTILS_H__

#include <Arduino.h>

class Output {
   public:
       static void initialize();
       static void printGameOver(int score);
       static void printNewPoint(int score);
       static void printNotte();
       static void printWelcomeAndDifficulty();
       static void printGo();
       static void printDifficulty(int difficulty);
       
};

#endif
