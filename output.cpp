#include "output.h"


Output::Output() {
  
}

void Output::initialize() {
  Serial.begin(9600);
}
void Output::printGameOver(int score)
{
  Serial.println("GAME OVER");
  Serial.print("Final Score: ");
  Serial.println(score);
}
void Output::printNewPoint(int score)
{
  Serial.print("New point! Score: ");
  Serial.println(score);
}
void Output::printNotte()
{
  Serial.println("Notte");
}
void Output::printWelcomeAndDifficulty()
{
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  Serial.println("Set difficulty level");
}
void Output::printGo()
{
  Serial.println("GO!");
}
void Output::printDifficulty(int difficulty)
{
  Serial.print("Difficulty set to: ");
  Serial.println(difficulty +1 );
}
