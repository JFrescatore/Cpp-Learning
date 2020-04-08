/*Jonathan Frescatore
Hanoi Solver, Odds Only
Use recursion to solve the Hanoi Problem. Use 3 as the base for the program and incrememnt to each odd number up till 7
*/

#include <iostream> //Input output
#include <math.h> //Pow
#include <cstdio> //getchar

using namespace std;

void hanoiSolver(int disks = 3, int startPeg = 1, int finalPeg = 0, int tmepPeg = 0);
int toHepta(int i_Number);

int main() {
  hanoiSolver();
  getchar();
  return 0;
}

void hanoiSolver(int disks, int startPeg, int finalPeg, int tempPeg){
  //Max used for correct ring placement, turn is recursion amounts, skips is dead turn
  
  static int i_MaxTurn = -1, i_Turn = -1, skips = 0; 
  int i_Hepta;

  if(i_MaxTurn == -1){
    i_MaxTurn = pow(2, disks);
    i_Turn = 0;
  }
  
  i_Turn++;
  i_Hepta = toHepta(i_Turn % 7);  //Every 7 turns will be 0 to indicate a "dead" turn
  
  if(i_Hepta == 0){ //Dead turn, ignore this turn and account for skip
    skips++;
  }else{
    if(i_Turn - skips == i_MaxTurn - pow(2, disks - 1)){
      disks--;
    }
    //Find startPeg
    if(i_Hepta == pow(2, 0) || i_Hepta == pow(2, 1))
      startPeg = 1; //Any turn that is equal to 2^0...2^8 is the move of a new piece
    else{
      if(i_Hepta == 3)
        startPeg = 3; //Turn 3 will be turn three
      else{
        if(i_Hepta % 3 == 0)
          startPeg = i_Hepta / 3; //Turns that convert to 6 will have 2 move
        else
          startPeg = i_Hepta % 3; //Any other turn not fiting either will be the remainder
      }
    } //End find startPeg

    //Fid tempPeg
    tempPeg = (i_Turn - skips) % 3 + 1;
    //End find tempPeg

    //Find finalPeg
    if(tempPeg == 2)
      finalPeg = tempPeg + startPeg;
    else if(tempPeg == 3)
      finalPeg = tempPeg - startPeg;
    else if(tempPeg == 1){
      if(startPeg == 1 || startPeg == 2)
        finalPeg = startPeg + tempPeg;
      else
        finalPeg = startPeg - tempPeg;
    } //End find finalPeg
      
    cout << "Turn: " << i_Turn - skips << endl;
    cout << "Move: " << startPeg << " -> " << finalPeg << endl;
    cout << "Disks Remaining: " << disks << endl << endl;
  } //End algorithm sequences

  if(disks == 0)
    return;

  hanoiSolver(disks, startPeg, finalPeg, tempPeg);
} //End hanoi solver

int toHepta(int i_Number){
  int i_Hepta = 0, position = 0, i_Remainder = 0;

  while(i_Number > 0){  //Octal is 1 - 7. Use 8 to get a value of 1 - 8
    i_Remainder = i_Number % 7; //Get the value of position
    i_Hepta += i_Remainder * pow(10, position); //Place remainder in correct position
    i_Number /= 7;  //Reduce number by 8
    position++; //Move position
  }

  return i_Hepta;
}



