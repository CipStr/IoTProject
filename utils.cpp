#include "utils.h"

timer::timer() {
  
}
void timer::startTimer() {
  initialTime = millis();
}
bool timer::checkExpired(int t) {
  if(millis() - initialTime >= t) {
    return true;
  }
  return false;
}
output::output() {
  
}
void output::printGameOver(int score)
{
  Serial.println("GAME OVER");
  Serial.print("Final Score: ");
  Serial.println(score);
}
void output::printNewPoint(int score)
{
  Serial.print("New point! Score: ");
  Serial.println(score);
}
void output::printNotte()
{
  Serial.println("Notte");
}
void output::printWelcomeAndDifficulty()
{
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  Serial.println("Set difficulty level");
}
void output::printGo()
{
  Serial.println("GO!");
}
void output::printDifficulty(int difficulty)
{
  Serial.print("Difficulty set to: ");
  Serial.println(difficulty +1 );
}


//LCD section
//void output::printGameOverLCD(int score)
//{
//  lcd.print("GAME OVER");
//  lcd.print("Final Score: ");
//  lcd.print(score);
//}
//void output::printNewPointLCD(int score)
//{
//  lcd.print("New point! Score: ");
//  lcd.print(score);
//}
//void output::printNotteLCD()
//{
//  lcd.print("Notte");
//}
//void output::printWelcomeAndDifficultyLCD()
//{
//  lcd.print("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
//  lcd.print("Set difficulty level");
//}
//void output::printGoLCD()
//{
//  lcd.print("GO!");
//}
//void output::printDifficultyLCD(int difficulty)
//{
//  lcd.print("Difficulty set to: ");
//  lcd.print(difficulty +1 );
//}
