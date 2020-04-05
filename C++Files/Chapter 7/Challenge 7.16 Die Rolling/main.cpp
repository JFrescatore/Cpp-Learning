#include <iostream> //Cin, Cout
#include <iomanip>  //output manipulation
#include <ctime>  //Time(NULL)
#include <stdlib.h> //srand
#include <fstream>  //Wrtting to file

using namespace std;

void rollDie(int iteration);
void finalCalculations(int i_Appearances[12]);

int main() {
  srand(time(NULL));  //Seed random
  rollDie(0); //Begin recursion
  return 0;
} //End main()

void rollDie(int iterations){
  int i_Die;
  static int i_Appearances[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  i_Die = (rand() % 6 - 0) + 1; //Range 0 - 5, add 1. Die roll 1
  i_Die += (rand() % 6 - 0) + 1;  //Second die roll
  
  i_Appearances[i_Die - 1] += 1;  //Taly the numbers appearances

  iterations++; //Recursion iteration track
  if(iterations <= 36000)  //Roll 36000 times
    rollDie(iterations);  //Continue reccursion
  else{
    finalCalculations(i_Appearances); //Final calculations
    return;
  }
} //End rollDie(int)

void finalCalculations(int i_Appearances[]){
  fstream file; //Create file
  file.open("Results.txt"); //Open file
  for(int i = 1; i < 12; i++){  //Write all recorded data, except entry [0]
    file << "Sum of " << i + 1 << " Appeared (" << i_Appearances[i] << ") times.\n"
      << "    Chance to appear: " << fixed << setprecision(2) 
      << ((float)i_Appearances[i] / 36000) * 100 << "%" << endl << endl;
  }
  file.close();
} //End finalCalculations(int[])