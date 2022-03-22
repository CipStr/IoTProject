#include <TimerOne.h>
#include <EnableInterrupt.h>
#define LED_PIN_RED 9
#define LED_PIN_A 10
#define LED_PIN_B 11
#define LED_PIN_C 12
#define LED_PIN_D 13
#define BUTTON_A 2
#define BUTTON_B 3
#define BUTTON_C 4
#define BUTTON_D 5
#define MAX_TIME 5000
#define MIN_TIME 3000

int current = 10;
int counter = 1;
int s = 100;
int t1;
int t2 = 1000;
unsigned long startTime;
unsigned long elapsedTime;

void setup() {
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_A, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  pinMode(LED_PIN_C, OUTPUT);
  pinMode(LED_PIN_D, OUTPUT);
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_C, INPUT);
  pinMode(BUTTON_D, INPUT);
  enableInterrupt(BUTTON_A, pressedButton, CHANGE);
  enableInterrupt(BUTTON_B, pressedButton, CHANGE);
  enableInterrupt(BUTTON_C, pressedButton, CHANGE);
  enableInterrupt(BUTTON_D, pressedButton, CHANGE);
  randomSeed(analogRead(0));
  t1 = random(MIN_TIME, MAX_TIME);
  startTime = millis();
  Serial.begin(9600);
  Serial.println(t1);
}
void pressedButton() {
  digitalWrite(LED_PIN_RED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  elapsedTime = millis();
  if(elapsedTime - startTime >= t1) {
    digitalWrite(current, HIGH);
    startTime = millis();
    delay(t2);
    digitalWrite(LED_PIN_RED, LOW);
  } else {
    noInterrupts();
    digitalWrite(current, LOW);
    if((current == 13 && counter == 1) || (current == 10 && counter == -1)) {
      counter = -counter;
    }
    current += counter;
    digitalWrite(current, HIGH);
    interrupts();
    delay(s);
  }
}
