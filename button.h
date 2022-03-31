#ifndef __BUTTON_H__
#define __BUTTON_H__

class Button {
    private:
        bool buttonPressed;
    public:
        int pin;
        Button(int pin);
        bool isCurrentlyPressed();
        
};

#endif