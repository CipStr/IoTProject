#include "TimerOne.h"
#include "EnableInterrupt.h"
#include <avr/sleep.h>
#define LED_PIN_RED 9
#define LED_PIN_L1 10
#define LED_PIN_L2 11
#define LED_PIN_L3 12
#define LED_PIN_L4 13
#define BUTTON_T1 2
#define BUTTON_T2 3
#define BUTTON_T3 4
#define BUTTON_T4 5
#define MAX_TIME 5000
#define MIN_TIME 3000

int current = 10;
int counter = 1;
int s = 100;;
int t1;
int t2 = 1000;
unsigned long startGameTime;
unsigned long elapsedGameTime;
int fadeAmount = 5;
int redFadeLevel = 0; 
bool isGameStarted = false;


void pressedButton() {
  digitalWrite(LED_PIN_RED, HIGH);
}
void sleepMode() {
  Serial.println("Notte");
  enableInterrupt(BUTTON_T1, wakeUp, CHANGE);
  enableInterrupt(BUTTON_T2, wakeUp, CHANGE);
  enableInterrupt(BUTTON_T3, wakeUp, CHANGE);
  enableInterrupt(BUTTON_T4, wakeUp, CHANGE);
}
void wakeUp() {
  sleep_disable();
}
void startGame() {
  disableInterrupt(BUTTON_T1);
  enableInterrupt(BUTTON_T1, pressedButton, CHANGE);
  enableInterrupt(BUTTON_T2, pressedButton, CHANGE);
  enableInterrupt(BUTTON_T3, pressedButton, CHANGE);
  enableInterrupt(BUTTON_T4, pressedButton, CHANGE);
  isGameStarted = true;
  startGameTime = millis();
}
void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_L1, OUTPUT);
  pinMode(LED_PIN_L2, OUTPUT);
  pinMode(LED_PIN_L3, OUTPUT);
  pinMode(LED_PIN_L4, OUTPUT);
  pinMode(BUTTON_T1, INPUT);
  pinMode(BUTTON_T2, INPUT);
  pinMode(BUTTON_T3, INPUT);
  pinMode(BUTTON_T4, INPUT);
  enableInterrupt(BUTTON_T1, startGame, CHANGE);
  randomSeed(analogRead(0));
  t1 = random(MIN_TIME, MAX_TIME);
  Timer1.initialize(100000000);
  Timer1.attachInterrupt(sleepMode);
}
void loop() {
  // put your main code here, to run repeatedly:
//  if(!isGameStarted) {
//    if((redFadeLevel >= 255 && fadeAmount > 0) || (redFadeLevel <= 0 && fadeAmount <0)) {
//      fadeAmount = -fadeAmount;
//    }
//    redFadeLevel += fadeAmount;
//    analogWrite(LED_PIN_RED, redFadeLevel);
//    delay(50);
//  } else {
//    elapsedGameTime = millis();
//    if(elapsedGameTime - startGameTime >= t1) {
//    // led fermo
//      digitalWrite(current, HIGH);
//      startGameTime = millis();
//      delay(t2);
//      digitalWrite(LED_PIN_RED, LOW);
//    } else {
//    // led in movimento
//      digitalWrite(current, LOW);
//      if((current == 13 && counter == 1) || (current == 10 && counter == -1)) {
//        counter = -counter;
//      }
//      current += counter;
//      digitalWrite(current, HIGH);
//      delay(s);
//    }
//  }
  
}
