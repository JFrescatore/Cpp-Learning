#pragma once
#include <iostream>
#include <vector>

class QueensEight {
public:
	QueensEight(int x_Board = 8, int y_Board = 8);
	~QueensEight();

	void handleMoves(int pos, bool active = false);
	void createBranch(int pos);
	int branchFail(int pos);
	void readPlacements();

	std::vector<int> getBoard();
	void convertOctalPos(int pos, int& x, int& y);
	int convertDecimalPos(int x, int y);

private:
	int x_Board, y_Board, queens, current_Branch = -1;
	std::vector<int> board;
	std::vector<int> branch;

};