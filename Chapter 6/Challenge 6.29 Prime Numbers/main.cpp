/*
  Jonathan Frescatore
  Prime Numbers: Find all prime numbers and output them in a chart
*/

#include <iostream> //Cin Cout
#include <iomanip>  //Set Width
#include <fstream>  //File

using namespace std;

bool checkPrime(int i_Number);

int main() {
  fstream primefile;
  primefile.open("PrimeNumbers.txt");
  int i_Number = 1,i_Count = 0;

  primefile << "Prime Numbers" << endl;

  while(i_Number < 10000){
    if(checkPrime(i_Number)){
      i_Count++;
      primefile << i_Number << ", ";  //Write the prime number into the file
      if(i_Count >= 9){
        primefile << endl;
        i_Count = 0;
      }
    }
    i_Number++; //increment
  }

  primefile.close();  //close file once done looping
}

bool checkPrime(int i_Number){  //Prime is a number with ONLY 2 divisors. itself, and 1
  int i_Divisors = 0;
  for(int i = 1; i <= i_Number; i++){
    if(i_Number % i == 0)
      i_Divisors++;
    if(i_Divisors > 2)  //If greater than 2 break, it is not prime
      break;
  }
  
  if(i_Divisors == 2) //Anything with 2 divisors after the iteration, its prime
    return true;
  else  //Any other amount is not prime
    return false;
}