#include <Arduino.h>
#include <EnableInterrupt.h>
#include <avr/sleep.h>
#include "timer.h"
#include "hardware.h"
#define N_GREEN_LEDS 4
#define N_RED_LEDS 1
#define N_BUTTONS 4
#define LED_PIN_RED 9
#define LED_PIN_L4 10
#define LED_PIN_L3 11
#define LED_PIN_L2 12
#define LED_PIN_L1 13
#define BUTTON_T1 2
#define BUTTON_T2 3
#define BUTTON_T3 4
#define BUTTON_T4 5
#define BOUNCING_TIME_OUT 150

Timer bouncingTimer;

// a reset function called on game over
void gameOver() {
    Output::printGameOver(Game::score);
    Game::goTo(State::GAME_OVER);
    Hardware::disableButtons();
    Hardware::enableStartGame(startGame);
    Hardware::setGreenLed(Hardware::ball, false);
}

void pressedButton() {
  if(Game::state == State::BALL_STOPPED) {
    Hardware::onButtonPressed();
  }
}
void sleepMode() {
  Game::goTo(State::SLEEP);
  Output::printNotte();
  Hardware::setButtonsEffect(wakeUp);
  Hardware::setRedLed(0, false);
  delay(100);
  Hardware::sleep();
}
void wakeUp() {
  Output::printWelcomeAndDifficulty();
  Hardware::wakeUp();
  bouncingTimer.startTimer();
  Hardware::enableStartGame(startGame);
}
void startGame() {
  if(bouncingTimer.checkExpired(BOUNCING_TIME_OUT)) {
    Output::printGo();
    Hardware::setButtonsEffect(pressedButton);
    Hardware::setRedLed(0, false);
    Game::startGame();    
  }
}
void setup() {
  Output::initialize();
  Output::printWelcomeAndDifficulty();

  Hardware::initialize(N_GREEN_LEDS, N_RED_LEDS, N_BUTTONS);
  int componentsPins[] = {LED_PIN_L1, LED_PIN_L2, LED_PIN_L3, LED_PIN_L4, LED_PIN_RED, BUTTON_T1, BUTTON_T2, BUTTON_T3, BUTTON_T4 };
  ComponentType componentsTypes[] = {GREEN_LED, GREEN_LED, GREEN_LED, GREEN_LED, RED_LED, BUTTON, BUTTON, BUTTON, BUTTON };
  Hardware::attachAll(componentsPins, componentsTypes);
  Hardware::enableStartGame(startGame);
  Game::initialize();
}

void loop() {
// GAME OVER
  if (Game::isGameOver()) {
    gameOver();
    delay(GAME_OVER_TIME);
    Game::goTo(State::WAIT_FOR_GAME);
  }
// FADING RED LED, GAME IS NOT STARTED YET
  else if (Game::isWaitingForGame()) {
    Hardware::readPotentiometer();
    Output::printDifficulty(Game::difficulty);
    Hardware::updateRedLeds();
    delay(50); // micro delay to avoid bouncing
// INGRESSO IN SLEEP
  } else if (Game::isSleepTime()) {
    sleepMode();
  }
// SIAMO IN PARTITA
  else {  
  // LED FERMO
    if(Game::isBallStopped()) {
      Hardware::setGreenLed(Hardware::ball, true);
      Game::goTo(State::BALL_STOPPED);
      delay(Game::t2);
      Hardware::checkNoInputGameOver();
    }
  // LED IN MOVIMENTO
    else { 
      Game::goTo(State::BALL_MOVING);
      Hardware::updateGreenLeds();
      delay(Game::s);
    }
  }
}
