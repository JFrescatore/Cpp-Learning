/*
Jonathan Frescatore
Function Template minimum: Write a program that uses a template and will return the 
smallest of two templates.

Test 1- class T = Int
  EntryA = 14, EntryB = 13
  Output: EntryA, 13

Test 2- class T = Float
  EntryA = 1.01, EntryB = 1.001
  Output: EntryB, 1.001

Test 3- class T = string  
  EntryA = @, EntryB = A (uses ascii code numbers)
  Output: @
*/

#include <iostream>

using namespace std;

template <class T>
T minimum(T entryA, T entryB);

int main() {
  int i = 14, ii = 13;
  float f = 1.01f, ff = 1.001f;
  string s = "@", ss = "A";

  cout << "Int: Entry A = 14, Entry B = 13\nSmallest: " << minimum(i, ii) << endl << endl;
  cout << "Float: Entry A = 1.01, Entry B = 1.001\nSmallest: " << minimum(f, ff) << endl << endl;
  cout << "String: Entry A = @, Entry B = A\nSmallest: " << minimum(s, ss) << endl << endl;
}

template <class T>
T minimum(T entryA, T entryB){
  if(entryA > entryB) //If Entry is greater, return b
    return entryB;

  return entryA;  //If it reaches here previous if was false, default return a
}