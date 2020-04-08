/*
Jonathan Frescatore
Calculating Number of seconds: write a function that returns the amount of seconds since 
the clock last struck 12.
*/

#include <iostream> //Cout, Cin

using namespace std;

int timeElapsed(int i_Hour, int i_Minutes, int i_Seconds);

int main() {
  cout << "Time: 6:51:32" << endl;
  cout << "Time Since last 12 o'clock: " << timeElapsed(6, 51, 32) << " seconds" << endl;
}

int timeElapsed(int i_Hour, int i_Minutes, int i_Seconds){
  int i_TotalSeconds = 0;
  i_TotalSeconds += i_Seconds;  //Seconds dont need conversion, add first
  i_TotalSeconds += i_Minutes * 60; //Convert minute to seconds, add

  if(i_Hour == 24)  //Hour 24 is 0
    i_Hour = 0;

  if(i_Hour >= 12)  //Convert military to am/pm
    i_Hour -= 12;
  i_TotalSeconds += i_Hour * (60 * 60); //Convert hours to seconds, add

  return i_TotalSeconds;
}
