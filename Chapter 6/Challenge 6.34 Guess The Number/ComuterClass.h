#include "ComputerClass.h"
#include <cmath>

using namespace std;

Computer::Computer(){
  seed = time(NULL);  //Default seed to time
  i_Number = 0; //Reset number
  i_GuessAmount = 0;  //Reset guesses
  i_Number = generateNumber(); //Gen new number
  startGame();  //Game Begins once everything is set
} //End Computer() base constructor

Computer::Computer(int seed){
  this -> seed = seed;  //Assign class seed to parameter seed
  i_Number = 0; //Reset number
  i_GuessAmount = 0;  //Reset Guesses
  i_Number = generateNumber(); //Gen new number
  startGame();  //Game begins once everything is set
} //End Computer(int) custom constructor

int Computer::generateNumber(){
  srand(seed);  //Apply the seed given.
  int i_RandNum = rand() % 1000 + 1; //Select number
  return i_RandNum;
} //End generateNumber()

void Computer::startGame(){
  cout << "I Have Picked a Random Number Between (1-1000).\nCan You Guess It?" << endl;
  getGuess();
}

void Computer::getGuess(){
  gameState = 1;
  int i_Guess;
  i_GuessAmount++;

  while(true){
    cout << "\nTurn (" << i_GuessAmount << ")" << endl; //State turn
    cout << "What is your guess? (1-1000)" << endl;

    cin >> i_Guess;

    if(i_Guess >= 1 && i_Guess <= 1000){
      break;
    }else{
      cout << "Not Within Range." << endl;
    } //End validation
  } //End while loop

  guess(i_Guess);
  if(gameState == 1)
    getGuess();
} //End getGuess()


void Computer::guess(int i_Guess){
  if(i_Closest == -1){
    i_Closest = i_Guess;
  }else if(abs(i_Closest - i_Number) > abs(i_Guess - i_Number)){
    i_Closest = i_Guess;
  } //Find closest guess

  if(i_Guess > i_Number + 50){
    cout << "To High" << endl;
  }else if(i_Guess > i_Number && i_Guess <= i_Number + 50){
    cout << "Lower" << endl;
  } //Guess to high

  if(i_Guess < i_Number - 50){
    cout << "To Low" << endl;
  }else if(i_Guess >= i_Number - 50 && i_Guess < i_Number){
    cout << "Higher" << endl;
  } //Guess to low

  if(i_GuessAmount % 10 == 0){
    for(int i = 0; i < 3; i++){
      cout << "\nCurrent Guess: " << i_GuessAmount << endl;
      cout << "You have been guessing a lot. Would you like to surrender? Y/N" << endl;
      
      string input = "";
      cin >> input;

      if(input == "Y" || input == "Yes")
        break;  //Break loop
      else if(input == "N" || input == "No")
        return; //Return function
      else
        cout << "Input not recognized" << endl;
    } //End for loop, after 3 questions the game will end.
    userLost(); //If yes the loop ended and reached here, if no the whole function was returned
  } //End asking if you  give up

  if(i_Guess == i_Number){
    userWon();
  } //User won
}

void Computer::userWon(){
  cout << "\nCongrats! You Won!" << endl;
  cout << "My Number: " << i_Number << endl;
  cout << "Total Turns: " << i_GuessAmount << endl;

  playAgain();
} //End userWon()

void Computer::userLost(){
  cout << "\nSorry You Lost." << endl;
  cout << "My Number: " << i_Number << endl;
  cout << "Closest Guess: " << i_Closest << endl;
  cout << "Total amount of turns: " << i_GuessAmount << endl;

  playAgain();
} //End userLost()

void Computer::playAgain(){
  for(int i = 0; i < 3; i++){
      cout << "\nWould You Like To Play Again? Y/N" << endl;
      
      string input = "";
      cin >> input;

      if(input == "Y" || input == "Yes"){
        break;
      }else if(input == "N" || input == "No"){
        gameState = 0;
        cout << "Good Bye!" << endl;
        return;
      }else
        cout << "Input not recognized" << endl;
    } //End for loop, after 3 questions the game will end.
    Computer();
}