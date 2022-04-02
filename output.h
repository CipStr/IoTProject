#ifndef __UTILS_H__
#define __UTILS_H__

#include <Arduino.h>

enum OutputMode : short {
    SERIAL_MONITOR = 0,
    LCD = 1,
};


class Output {
    private:
        // Output mod: can be set to SERIAL MONITOR or other
        static OutputMode mode;
    public:
        // MUST be called before using any other method of the Output class
        static void initialize(OutputMode mode);
        // Sets output mode
        static void setMode(OutputMode mode);
        // Prints Game over message
        static void printGameOver(int score);
        // Prints new point message
        static void printNewPoint(int score);
        // Prints message when going to sleep
        static void printNotte();
        // Prints welcome message
        static void printWelcomeAndDifficulty();
        // Prints starting game message
        static void printGo();
        // Prints current difficulty message
        static void printDifficulty(int difficulty);
};

#endif
