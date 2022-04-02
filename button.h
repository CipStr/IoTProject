#ifndef __BUTTON_H__
#define __BUTTON_H__

class Button {
    private:
        // Autoexplicative
        bool buttonPressed;
    public:
        int pin;
        Button(int pin);
        // Uses button voltage to know if this button is currently been pressed
        bool isCurrentlyPressed();
        
};

#endif