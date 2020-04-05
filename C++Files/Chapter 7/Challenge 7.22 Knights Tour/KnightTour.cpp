#include "KnightTour.h"

using namespace std;

KnightTour::KnightTour(int x_Board, int y_Board){
  this -> x_Board = x_Board;
  this -> y_Board = y_Board;

  file.open("ToursPossible.txt", fstream::app);
  file << "Board: " << x_Board << "x" << y_Board << endl;
  buildBoard();
}

KnightTour::~KnightTour(){

}

inline void KnightTour::buildBoard(){
  board.clear();
  for(int x = 0; x < x_Board; x++){
    for(int y = 0; y < y_Board; y++){
      Pair3D pair;
      pair.y_axis = y + 1;
      pair.x_axis = x + 1;
      board.push_back(pair);
    }
  } //End position population

  //Every 2 turns X increases by 1, and y will be either 1 or 2 based on x.
  //This tests every move possible by the Knight to see for legal moves.
  int safeguard_X, safeguard_Y;
  for(int i = 0; i < board.size(); i++){
    board[i].moves = futureMoves(board[i].x_axis, board[i].y_axis, safeguard_X, safeguard_Y);
   // cout << "Position: " << board[i].x_axis << ", " << board[i].y_axis << "| " << board[i].moves << endl;
  } //End move population chart
  moveKnight(1, 1); //Begin playing
} //End buildBoard()

//The function calling this will decided which data it needs to use, and which it ignores.
int KnightTour::futureMoves(int x_Position, int y_Position, int &x_Future, int &y_Future){
  Pair3D future_Square;
  future_Square.moves = 9;  //Not possible move, allows proper swapping occurs
  future_Square.x_axis = 0; //Not possible, if still 0 no move possible
  future_Square.y_axis = 0; //Not possible, if still 0 no move possible

  int x_Offset = -3, y_Offset = -1, i_Moves = 0; //Default base is -3 -1.
  for(int i = 0; i < 8; i++){
    int temp_X, temp_Y; //Finds potential position

    if(i % 2 == 0){ //IF turn is even, increase x, and change y accordingly
        x_Offset++;
        if(x_Offset == 0) //Skip 0, move to 1
          x_Offset = 1;

        //Y must always be either 1 or 2. 2 if x = 1, 1 if x = 2
        if(abs(x_Offset) == 1)  
          y_Offset = -2;
        else if(abs(x_Offset) == 2)
          y_Offset = -1;
      } //Control X_Offset repeating

      temp_X = x_Position + x_Offset;
      temp_Y = y_Position + y_Offset;

      if(temp_X > 0 && temp_X <= x_Board && temp_Y > 0 && temp_Y <= y_Board){
        i_Moves++;  //If valid, increment moves
        if(board[(temp_X * x_Board - x_Board) + (temp_Y - 1)].active == 1){
          //Find this legal move
          Pair3D pair = board[(temp_X * x_Board - x_Board) + (temp_Y - 1)]; 
          if(pair.moves < future_Square.moves)
            future_Square = pair;   //IF new move has less moves, swap
        }
      }

      y_Offset *= -1; //Flip y offset
  }

  x_Future = future_Square.x_axis;  //"Return" future x
  y_Future = future_Square.y_axis;  //"Return" future y
  return i_Moves; //Return moves
} //End futureMoves(int, int, int&, int&)

void KnightTour::moveReduction(int x_Position, int y_Position){
  Pair3D pair = board[(x_Position * x_Board - x_Board) + (y_Position - 1)];
  pair.moves--;

  int x_Offset = -3, y_Offset = -1, i_Moves = 0; //Default base is -3 -1.
  for(int i = 0; i < 8; i++){
    int temp_X, temp_Y;

    if(i % 2 == 0){ //IF turn is even, increase x, and change y accordingly
        x_Offset++;
        if(x_Offset == 0) //Skip 0, move to 1
          x_Offset = 1;

        //Y must always be either 1 or 2. 2 if x = 1, 1 if x = 2
        if(abs(x_Offset) == 1)  
          y_Offset = -2;
        else if(abs(x_Offset) == 2)
          y_Offset = -1;
      } //Control X_Offset repeating

      temp_X = x_Position + x_Offset;
      temp_Y = y_Position + y_Offset;

      if(temp_X > 0 && temp_X <= x_Board && temp_Y > 0 && temp_Y <= y_Board){
        if(board[(temp_X * x_Board - x_Board) + (temp_Y - 1)].active == 1)
          //Reduce moves to reflect a knight moving
          board[(temp_X * x_Board - x_Board) + (temp_Y - 1)].moves--; 
      } //Find legal moves, and reduce as 

      y_Offset *= -1; //Flip y offset
  } //End all move reduction
} //End moveReduction(int, int)


void KnightTour::moveKnight(int x_Position, int y_Position){
  static int turn = 0;
  turn++;
  int x_Future, y_Future; //Used to get future positions
  //Find current position and turn active off
  board[(x_Position * x_Board - x_Board) + (y_Position - 1)].active = 0;
  futureMoves(x_Position, y_Position, x_Future, y_Future);  //Get future x, y

  if(x_Future == 0 && y_Future == 0){ //IF future is 0, 0. No legal moves possible. 
    if(turn == x_Board * y_Board){  //IF the turn is at the max amount, it passed
      file << " Tour Possible." << endl << endl;
      file.close();
      turn = 0;
      return;
    }else{  //Anything short is a dead end, and failed.
      file << " Tour not Possible." << endl << endl;
      file.close();
      turn = 0;
      return;
    }
  } //End validation

  moveReduction(x_Position, y_Position);  //Reduce possible moves for all legal squares
  //outputFormated(x_Position, y_Position, x_Future, y_Future, turn); //Output the moves

  moveKnight(x_Future, y_Future);
} //End moveKnight(int, int)

void KnightTour::outputFormated(int x_Position, int y_Position, int x_Future, int y_Future, int turn){

  char x_Character = 96 + x_Position, x_FutureChar = 96 + x_Future;
  file << "   Turn " << turn << "\n  Move: " << x_Character << y_Position << " -> "
    << x_FutureChar << y_Future << "." << endl << endl;
} //End outputFormated(int, int, int, int)

void KnightTour::wipeData(){
  file.open("ToursPossible", fstream::out | fstream::trunc);
  file.close();
} //End wipeData()