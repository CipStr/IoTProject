#include "game.h"

void Game::initialize() {
    t3 = SLEEP_TIMER;    
    t2 = DEFAULT_DIFFICULTY_TIME;   // maximum time in which the button can be pressed
    s = DEFAULT_SPEED;   
    f = DIFFICULTY_SCALE;
    score  = 0;
    sleepTimer.startTimer();
    isGameStarted = false;
    Game::randomT1();
}

void Game::gameOver() {
    difficulty = -1;
    s= DEFAULT_SPEED;
    t2 = DEFAULT_DIFFICULTY_TIME;
    score = 0;
    state = State::GAME_OVER;
    isGameStarted = false;
}
void Game::fadingRed() {
    sleepTimer.startTimer();
}

void Game::newPoint() {
    score++;
    state = State::BALL_MOVING;
    t2 *= f;
    s *= f;
}

void Game::goToSleep() {
    sleepTimer.startTimer();
    difficulty = -1;
}

// difficulty level goes from 1 to 8
void Game::setDifficultyTime() {
  Game::f -= 0.05 * Game::difficulty;
}

void Game::randomT1() {
    t1 = Hardware::randomBetween(MIN_TIME, MAX_TIME);
}

bool Game::isGameOver() {
    return Game::state == State::GAME_OVER;
}

void Game::startGame() {
    Game::setDifficultyTime();
    timer1.startTimer();
    isGameStarted = true;
}

void Game::goTo(State state) {
    switch (state) {
        case GAME_OVER:
            Game::gameOver();
            break;
        case BALL_MOVING:
            state = BALL_MOVING;
            break;
        case WAIT_FOR_GAME:
            Game::fadingRed();
            break;
        case BALL_STOPPED:
            state = BALL_STOPPED;
            timer1.startTimer();
            break;
        case SLEEP:
            Game::goToSleep();
            break;
    }
}

bool Game::isWaitingForGame() {
    return !isGameStarted && !sleepTimer.checkExpired(t3);
}

bool Game::isSleepTime() {
    return !isGameStarted && sleepTimer.checkExpired(t3);
}

bool Game::isBallStopped() {
    return timer1.checkExpired(t1);
}

bool Game::isBallMoving() {

}