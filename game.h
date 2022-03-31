#ifndef __GAME_H__
#define __GAME_H__

#include "hardware.h"
#include "timer.h"
#define DIFFICULTY_SCALE 0.9
#define GAME_OVER_TIME 10000
#define DEFAULT_DIFFICULTY_TIME 1000
#define DEFAULT_SPEED 100
#define SLEEP_TIMER 10000
#define MAX_TIME 5000
#define MIN_TIME 3000 //milliseconds

enum State : short {
    NO_STATE = 0,
    BALL_MOVING = 1,
    BALL_STOPPED = 2,
    GAME_OVER = 3,
    WAIT_FOR_GAME = 4,
    SLEEP = 5,
};

class Game {
    private:     
        static Timer timer1;
        static Timer sleepTimer;
        static bool isGameStarted;
        static void setDifficultyTime();
        static void randomT1();
        static void gameOver();
        static void fadingRed();
        static void goToSleep();
    public:
        static short difficulty; // related to the potentiometer, from 1 to 8
        static State state; // "gamestate", "programstate"
        static void initialize();
        static int t1;  // random time for LED to stop
        static int t2;  // maximum time in which the button can be pressed
        static int t3; 
        static int s;           // changing LED speed
        static float f;
        static int score;
        static void goTo(State state);   
        static void newPoint();
        static void startGame();
        static bool isGameOver();
        static bool isWaitingForGame();
        static bool isSleepTime();
        static bool isBallStopped();
        static bool isBallMoving();
        
};

#endif 