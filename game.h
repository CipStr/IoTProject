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

// Utility enum to define all game states
enum State : short {
    NO_STATE = 0,
    BALL_MOVING = 1,
    BALL_STOPPED = 2,
    GAME_OVER = 3,
    WAIT_FOR_GAME = 4,
    SLEEP = 5,
};

// Model class, not Arduino dependent
class Game {
    private:
        // First timer, detect ball stopping time
        static Timer timer1;
        // Sleep timer, when expired it is time for sleep
        static Timer sleepTimer;
        // True when game has started
        static bool isGameStarted;
        // Used by "startGame" method, sets the time that determines game's difficulty
        static void setDifficultyTime();
        // Calculates random t1 using MIN_TIME and MAX_TIME
        static void randomT1();
        // Resets game's variables after game over
        static void gameOver();
        // Starts sleep timer during Fading red phase
        static void fadingRed();
        // Utility method to go to sleep phase
        static void goToSleep();
    public:
        // Related to the potentiometer, from 1 to 8
        static short difficulty;
        // "Game state", "Program state". Represents the state of the current program running 
        static State state; 
        // Most important method. MUST be called before anything else.
        static void initialize();
        // Random time for BALL to stop
        static int t1;
        // Maximum time in which the button can be pressed  
        static int t2;
        // Time used as countdown for sleep during WAIT FOR GAME phase
        static int t3; 
        // Time for ball to pass from one led to another
        static int s;           
        // Delay calculated using game's difficulty
        static float f;
        // Score of the game
        static int score;
        // One of the main methods: used as transition between states
        static void goTo(State state);
        // Method to increase score
        static void newPoint();
        // Method called when game is started. Sets difficulty times and timers
        static void startGame();
        // Checks if game is over
        static bool isGameOver();
        // Checks if we are in WAIT FOR GAME state
        static bool isWaitingForGame();
        // Checks if the system is supposed to go to sleep
        static bool isSleepTime();
        // Checks if ball is idle
        static bool isBallStopped();
        // Checks if ball is moving (true only during game phase)
        static bool isBallMoving();
        
};

#endif 