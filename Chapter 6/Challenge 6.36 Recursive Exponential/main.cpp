/*
  Jonathan Frescatore
  Recursive Exponential: Use recursion to replicate power. 
*/

#include <iostream>

using namespace std;

int power(int base, int exponent);

int main() {
  int i = power(3, 2);  //3^2 = 9
  cout << i << endl;

  i = power(5, 3);  //5^3 = 25 * 5 = 125
  cout << i << endl;
} //End main()

inline int power(int base, int exponent){
  static int originalBase = -1;  //Static variable to used to reduce parameters

  if(originalBase == -1)
    originalBase = base;  //The original base is needed to repeat multiplication

  if(exponent > 1){ //If exponent is greater than 1, do the math
    exponent--;
    base *= originalBase;
    return power(base, exponent); //Recall itself with the new base and exponent
  }else{
    originalBase = -1;  //Reset static variable for future use
    return base;  //End the loop and return the base back up the function trail
  }
} //End power(int, int). DOES NOT HANDLE NEGATIVE OR FRACTIONS