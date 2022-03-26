#include <TimerOne.h>
#include <EnableInterrupt.h>
#include <avr/sleep.h>

//#include <LiquidCrystal.h>
#include "utils.h"

//LiquidCrystal lcd(, , , , , );

#define LED_PIN_RED 9
#define LED_PIN_L4 10
#define LED_PIN_L3 11
#define LED_PIN_L2 12
#define LED_PIN_L1 13
#define BUTTON_T1 2
#define BUTTON_T2 3
#define BUTTON_T3 4
#define BUTTON_T4 5
#define POT_PIN A2
#define MAX_TIME 5000
#define MIN_TIME 3000
#define BOUNCING_TIME_OUT 150
#define LED_IDLE 0
#define LED_MOVING 1
#define GAME_OVER 2
#define DIFFICULTY_SCALE 0.9
#define SPEED_SCALE 0.9
#define GAME_OVER_TIME 10000
#define DEFAULT_DIFFICULTY_TIME 1000
#define DEFAULT_SPEED 100
#define SLEEP_TIMER 10000
int difficulty = 0;                 // related to the potentiometer, from 1 to 8
int state = 3;                      // "gamestate", "programstate"
int current = 0;                    // current LED
int counter = 1;                    // LED switcher
int s = DEFAULT_SPEED;              // changing LED speed
int t1;                             // random time for LED to stop
int t2 = DEFAULT_DIFFICULTY_TIME;   // maximum time in which the button can be pressed
int t3 = SLEEP_TIMER;               // sleep timer
unsigned long sleepTimer;           // sleep timer counter
unsigned long startGameTime;        // game started timestamp
unsigned long elapsedGameTime;      // elapsed time during the last game loop
unsigned long timeStamp;            //
int fadeAmount = 5;
int redFadeLevel = 0; 
bool isGameStarted = false;
int leds[4];
int buttons[4];
int score = 0;
bool buttonPressed = false;
output out;
// a reset function called on game over
void gameOver() {
  out.printGameOver(score);
  //utils::output::printGameOverLCD(score);
  /*
  Serial.println("GAME OVER");
  Serial.print("Final Score: ");
  Serial.println(score);
  */
  isGameStarted = false;
  score = 0;
  state = LED_MOVING;
  for(int i= 0; i < 4; i++) {
      disableInterrupt(buttons[i]);
   }
   enableInterrupt(BUTTON_T1, startGame, RISING);
   digitalWrite(leds[current], LOW);
   difficulty = -1;
   s= DEFAULT_SPEED;
   t2 = DEFAULT_DIFFICULTY_TIME;
}
// difficulty level goes from 1 to 8
void setDifficultyTime(int difficultyLevel) {
  //use pow
  for (int i = 0; i < difficultyLevel; i++) {
    t2 *= DIFFICULTY_SCALE;
    s *= SPEED_SCALE;
  }
}

void pressedButton() {
  if(state == LED_IDLE) {
    buttonPressed = true;
    for(int i = 0; i < 4; i++) {
      if(digitalRead(buttons[i]) == HIGH) {      
        if(current == i) {
          score += 1;
          out.printNewPoint(score);
          //utils::output::printNewPointLCD(score);
          /*
          Serial.print("New point! Score: ");
          Serial.println(score);
          */
          state = LED_MOVING;
          t2 *= DIFFICULTY_SCALE;
          s *= SPEED_SCALE;
        } else {
         state = GAME_OVER;
        }
      }
    } 
  }
}
void sleepMode() {
  out.printNotte();
  //utils::output::printNotteLCD();
  /*
  Serial.println("Notte");
  */
  for(int i= 0; i < 4; i++) {
    enableInterrupt(buttons[i], wakeUp, RISING);
  }
  digitalWrite(LED_PIN_RED, LOW);
  difficulty = -1;
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}
void wakeUp() {
  out.printWelcomeAndDifficulty();
  //utils::output::printWelcomeAndDifficulty();
  /*
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  Serial.println("Set difficulty level");
  */
  sleep_disable();
  timeStamp = millis();
  enableInterrupt(BUTTON_T1, startGame, RISING);
}
void startGame() {
  if(millis() - timeStamp >= BOUNCING_TIME_OUT) {
    out.printGo();
    //utils::output::printGoLCD();
    /*
    Serial.println("GO!");
    */
    for(int i= 0; i < 4; i++) {
      enableInterrupt(buttons[i], pressedButton, RISING);
    }
    digitalWrite(LED_PIN_RED, LOW);
    isGameStarted = true;
    setDifficultyTime(difficulty);
    startGameTime = millis();
    
  }
}
void setup() {
  Serial.begin(9600);
  out.printWelcomeAndDifficulty();
  //utils::output::printWelcomeAndDifficultyLCD();
  /*
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  Serial.println("Set difficulty level");
  */
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
  sleepTimer = millis();
  enableInterrupt(BUTTON_T1, startGame, CHANGE);
  t1 = random(MIN_TIME, MAX_TIME);
}
void loop() {
  if (state == GAME_OVER) {
    gameOver();
    delay(GAME_OVER_TIME);
    sleepTimer = millis();
  }
  else if(!isGameStarted && (millis() - sleepTimer <= t3)) {
    // FADING RED LED, GAME IS NOT STARTED YET
    if((redFadeLevel >= 255 && fadeAmount > 0) || (redFadeLevel <= 0 && fadeAmount <0)) {
      fadeAmount = -fadeAmount;
    }
    int potValue = analogRead(POT_PIN);
    if (map(potValue, 0, 1023, 0, 7) != difficulty) {
      difficulty = map(potValue, 0, 1023, 0, 7);
      out.printDifficulty(difficulty);
      //utils::output::printDifficultyLCD(difficulty);
      /*
      Serial.print("Difficulty set to: ");
      Serial.println(difficulty +1 );
      */
    }
    redFadeLevel += fadeAmount;
    analogWrite(LED_PIN_RED, redFadeLevel);
    delay(50);
  } else if(!isGameStarted && (millis() - sleepTimer >= t3)) {
    //ingresso in sleep
    sleepTimer = millis();
    sleepMode();
  }
  else {
    //siamo in partita
    elapsedGameTime = millis();
    if(elapsedGameTime - startGameTime >= t1) {
    // led fermo
      state = LED_IDLE;
      digitalWrite(leds[current], HIGH);
      startGameTime = millis();
      delay(t2);
      
      if (!buttonPressed) {
        state = GAME_OVER;
      } else {
        buttonPressed = false;
      }
    } else {
      state = LED_MOVING;
    // led in movimento
      digitalWrite(leds[current], LOW);
      if((current == 3 && counter == 1) || (current == 0 && counter == -1)) {
        counter = -counter;
      }
      current += counter;
      digitalWrite(leds[current], HIGH);
      delay(s);
    }
  }
  
}
