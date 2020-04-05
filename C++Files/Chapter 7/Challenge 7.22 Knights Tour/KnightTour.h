#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Pair3D.h"

class KnightTour{
public:
  KnightTour(int x_Board = 8, int y_Board = 8); //Builds board, default 8 by 8
  ~KnightTour();

  //Populate and tally possible moves for each posiiton
  void buildBoard();

  int futureMoves(int x_Position, int y_Position, int &x_Future, int &y_Future);

  void moveKnight(int x_Position = 0, int y_Position = 0);

  //Reduce the possible moves of each position the knight reaches. Branching.
  void moveReduction(int x_Position, int y_Position);
  void outputFormated(int x_Position, int y_Position, int x_Future, int y_Future, int turn);

  void wipeData();
private:
  std::vector<Pair3D> board;
  std::ofstream file;
  int x_Board, y_Board;
};