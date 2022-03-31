#ifndef __HARDWARE_H__
#define __HARDWARE_H__
#include "led.h"
#include "button.h"
#include "game.h"
#include "output.h"
#include <Arduino.h>
#include <EnableInterrupt.h>
#define POT_PIN A2

enum ComponentType : short {
    GREEN_LED = 0,
    RED_LED = 1,
    BUTTON = 2,
};

class Hardware {
    private:
        static short currentGLedPos;
        static short currentRLedPos;
        static short currentButton;
        static int greenLedCounter; // for green led switching
        static void initializeLeds();
        static void initializeButtons();
        static int n_greenLeds; 
        static int n_redLeds;
        static int n_buttons;
    public:
        static void initialize(int numberOfGreenLeds, int numberOfRedLeds, int numberOfButtons);
        static GreenLed** greenLeds;
        static RedLed** redLeds;
        static Button** buttons;
        static int ball;            // green led currently active
        static bool buttonPressed;
        static void attachComponent(int pin, ComponentType type);
        static long randomBetween(int min, int max);
        static void readPotentiometer();
        static void attachAll(int pins[], ComponentType types[]);
        static void disableButtons();
        static void enableStartGame(interruptFunctionType startGameFunction);
        static void setButtonsEffect(interruptFunctionType effectFunction);
        static void setGreenLed(int position, bool state);
        static void setRedLed(int position, bool state);
        static void updateRedLeds();
        static void updateGreenLeds();
        static bool isBall(int position);
        static void sleep();
        static void wakeUp();

        static void onButtonPressed();        // game buttons' behaviours
        static void checkNoInputGameOver();
};

#endif