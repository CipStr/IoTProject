#ifndef __LED_H__
#define __LED_H__

// Abstract class for leds 
class Led {
    private:
        // Autoexplicative
        bool isOn;
    public:
        Led();
        // Constructor to set the pin
        Led(int pin);
        // Virtual method. Must be extended by all sub-classes of Led's class
        virtual void turnOn() = 0;
        // Virtual method. Must be extended by all sub-classes of Led's class
        virtual void turnOff() = 0;
};

class RedLed : Led{
    private:
        // Analog intensity of the led between 0 and 255
        int intensity;
        // Speed of the fading effect
        int fadeAmount;
    public:
        // Pin of this led
        int pin;
        RedLed(int pin);
        RedLed();
        // Updates intensity of the led using fade effect
        void updateIntensity();
        void turnOff();
        void turnOn();
        // Sets this led's state
        void setState(bool state);
};

class GreenLed : Led{
    public:
        int pin;
        GreenLed(int pin);
        GreenLed();
        void turnOff();
        void turnOn();
        void setState(bool state);
};


#endif