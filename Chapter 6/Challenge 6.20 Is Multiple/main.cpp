/*
  Jonathan Frescatore
  Multiple: Write a function that takes in two intergers, return true or false if 
  the second number is a Multiple of the first
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>

using namespace std;

bool isMultiple(int i_Base, int i_Possible);

int main() {
  fstream multipleFile;
  multipleFile.open("Multiples.txt");
  multipleFile << "Base" << setw(5) << " " << "Multiples" << endl;
  int i_Base = 1, i_Multiple = 1;

  while(i_Base <= 100){
    multipleFile << setw(4) << right << i_Base << setw(4) << " ";
    while(i_Multiple <= 100){
      if(isMultiple(i_Base, i_Multiple)){
        multipleFile << i_Multiple << ", ";
      }
      i_Multiple++;
    }
    multipleFile << endl;
    i_Multiple = 1;
    i_Base++;
  }
  getchar();
  return 0;
}


bool isMultiple(int i_Base, int i_Possible){
  if(i_Possible % i_Base == 0)
    return true;
  return false;
}