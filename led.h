#ifndef __LED_H__
#define __LED_H__

class Led {
    private:
        bool isOn;
    public:
        Led();
        Led(int pin);
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
};

class RedLed : Led{
    private:
        int intensity;
        int fadeAmount;
    public:
        int pin;
        RedLed(int pin);
        RedLed();
        void updateIntensity();
        void turnOff();
        void turnOn();
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