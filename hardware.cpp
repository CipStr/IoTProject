#include "hardware.h"

void Hardware::initialize(int numberOfGreenLeds, int numberOfRedLeds, int numberOfButtons) {
    Hardware::buttons = new Button*[numberOfButtons]();
    Hardware::greenLeds = new GreenLed*[numberOfGreenLeds]();
    Hardware::redLeds = new RedLed*[numberOfRedLeds](); 
    Hardware::n_buttons = numberOfButtons;
    Hardware::n_greenLeds = numberOfGreenLeds;
    Hardware::n_redLeds = numberOfRedLeds;
    currentGLedPos = 0;
    currentRLedPos = 0;
    currentButton = 0;
    ball = 0;
    greenLedCounter = 1;
/*
    leds[0] = LED_PIN_L1;
    leds[1] = LED_PIN_L2;
    leds[2] = LED_PIN_L3;
  leds[3] = LED_PIN_L4;
  buttons[0] = BUTTON_T1;
  buttons[1] = BUTTON_T2;
  buttons[2] = BUTTON_T3;
  buttons[3] = BUTTON_T4;
  for(int i= 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT);
  }
  */
}
void Hardware::initializeLeds() {
    for (int i = 0; i< n_greenLeds; i++ ) {
        pinMode(greenLeds[i]->pin, OUTPUT);
    }
    for (int i = 0; i< n_redLeds; i++ ) {
        pinMode(redLeds[i]->pin, OUTPUT);
    } 
}

void Hardware::initializeButtons() {
    for (int i = 0; i < n_buttons; i++) {
        pinMode(buttons[i]->pin, INPUT);
    }
}

long Hardware::randomBetween(int min, int max) {
    return random(min, max);
}

void Hardware::readPotentiometer() {
    int potValue = analogRead(POT_PIN);
    if (map(potValue, 0, 1023, 0, 7) != Game::difficulty) {
        Game::difficulty = map(potValue, 0, 1023, 0, 7);
    }
}

void Hardware::attachComponent(int pin, ComponentType type) {
    switch (type) {
        case GREEN_LED:
            Hardware::greenLeds[currentGLedPos] = new GreenLed(pin);
            currentGLedPos++;
            break;
        case RED_LED:
            Hardware::redLeds[currentRLedPos] = new RedLed(pin);
            currentRLedPos++;
            break; 
        case BUTTON:
            Hardware::buttons[currentButton] = new Button(pin);
            currentButton++;
            break;
    }
}

void Hardware::attachAll(int pins[], ComponentType types[]) {
    for (int i = 0; i< sizeof(pins); i++) {
        Hardware::attachComponent(pins[i], types[i]);
    }
}

void Hardware::disableButtons() {
    for(int i= 0; i < n_buttons; i++) {
        disableInterrupt(buttons[i]->pin);
    }
}
void Hardware::enableStartGame(interruptFunctionType startGameFunction) {
    enableInterrupt(buttons[0]->pin, startGameFunction, RISING);
}
void Hardware::setButtonsEffect(interruptFunctionType effectFunction) {
    for (int i = 0 ; i < n_buttons; i++) {
        enableInterrupt(buttons[i]->pin, effectFunction, RISING);
    }
}
void Hardware::setGreenLed(int position, bool state) {
    greenLeds[position]->setState(state);
}
void Hardware::setRedLed(int position, bool state) {
    redLeds[position]->setState(state);
}

void Hardware::updateRedLeds() {
    for (int i = 0; i< n_redLeds; i++ ) {
        redLeds[i]->updateIntensity();
    } 
}

void Hardware::updateGreenLeds() {
    greenLeds[ball]->turnOff();
      if((ball == n_greenLeds-1 && greenLedCounter == 1) || (ball == 0 && greenLedCounter == -1)) {
        greenLedCounter = -greenLedCounter;
      }
      ball += greenLedCounter;
      greenLeds[ball]->turnOn();
}
bool Hardware::isBall(int position) {
    return Hardware::ball == position;
}

void Hardware::onButtonPressed() {
    Hardware::buttonPressed = true;
    for(int i = 0; i < n_buttons; i++) {
        if(Hardware::buttons[i]->isCurrentlyPressed()) {      
            if(Hardware::isBall(i)) {
                Game::newPoint();
                Output::printNewPoint(Game::score);
            } else {
                Game::state = State::GAME_OVER;
            }
            return;
        }
    } 
}

void Hardware::sleep() {
    //set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    // sleep_enable();
    //sleep_mode();
}

void Hardware::wakeUp() {
    //sleep_disable();
}

void Hardware::checkNoInputGameOver() {
    if (!Hardware::buttonPressed) {
        Game::state = GAME_OVER;
    } else {
        Hardware::buttonPressed = false;
    }
}