#include <iostream>
#include <stdlib.h>
#include <time.h>

class Computer{
public: 
  Computer();
  Computer(int seed);

  int generateNumber();

  void startGame();

  void getGuess();
  void guess(int i_Guess);

  void userWon();
  void userLost();
  void playAgain();

private:
  int seed;
  int i_Number;
  int i_GuessAmount = 0;
  int i_Closest = -1;
  int gameState = 0;
};