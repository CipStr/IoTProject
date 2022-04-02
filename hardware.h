#ifndef __HARDWARE_H__
#define __HARDWARE_H__
#include "led.h"
#include "button.h"
#include "game.h"
#include "output.h"
#include <Arduino.h>
#include <EnableInterrupt.h>
#define POT_PIN A2

// Utility Enum to distinguish component types
enum ComponentType : short {
    GREEN_LED = 0,
    RED_LED = 1,
    BUTTON = 2,
};

// Main class. Contains high level methods to deal with more counterintuitive Arduino functions
class Hardware {
    private:
        // Current positions of the next free space for components inside corresponding arrays
        static short currentGLedPos;
        static short currentRLedPos;
        static short currentButton;

        static int greenLedCounter; // for green led switching

        // Initialize Leds and Buttons with pinModes 
        // Called by "initialize" function
        static void initializeLeds();
        static void initializeButtons();

        // Sizes of Components' arrays
        static int n_greenLeds; 
        static int n_redLeds;
        static int n_buttons;
    public:
        // Starting function. No other function should be called before calling this. 
        static void initialize(int numberOfGreenLeds, int numberOfRedLeds, int numberOfButtons);

        // Array of components.
        static GreenLed** greenLeds;
        static RedLed** redLeds;
        static Button** buttons;

        // Index of current active green Led
        static int ball;
        // Modified each time the ball stops.
        // Registers player input to know if the player has pressed at least one button
        static bool buttonPressed;
        // Insert new component. Called by "attachAll"
        static void attachComponent(int pin, ComponentType type);
        // Insert multiple components at once
        static void attachAll(int pins[], ComponentType types[]);
        // Return a random number between min(inclusive) and max(exclusive) using Arduino random function
        static long randomBetween(int min, int max);
        // Reads potentiometer(set on POT_PIN) value and sets Game difficulty 
        static void readPotentiometer();
        // Disables buttons removing all interrupts functions
        static void disableButtons();
        // Sets start game function ONLY TO FIRST BUTTON of the components array
        static void enableStartGame(interruptFunctionType startGameFunction);
        // Sets interrupt function to ALL buttons 
        static void setButtonsEffect(interruptFunctionType effectFunction);
        // Sets state of the green led placed at "position" index of the component array
        static void setGreenLed(int position, bool state);
        // Sets state of the red led placed at "position" index of the component array
        static void setRedLed(int position, bool state);
        // Call update function of all red leds
        static void updateRedLeds();
        // Updates the position of the ball
        static void updateGreenLeds();
        // Returns whether the green led at "position" index represents current ball position
        static bool isBall(int position);
        // Goes to sleep mode
        static void sleep();
        // Disable sleep mode
        static void wakeUp();

        // Calls button behaviour during game time. 
        // Uses button voltage to know which of the buttons is pressed
        static void onButtonPressed();        
        // Detects whether the player has pressed the button at the right time. 
        // If no button is detected, game over is called
        static void checkNoInputGameOver();
};

#endif