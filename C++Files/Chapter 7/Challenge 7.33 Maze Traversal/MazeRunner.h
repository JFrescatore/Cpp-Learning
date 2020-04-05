#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>

class MazeRunner {
public:
	MazeRunner(int maze_Width = 12, int maze_Height = 12);
	~MazeRunner();

	void buildMaze();
	void mazeTraverse(int x_Position, int y_Position, int forward);

	void lookDirection(int &x_Pos, int &y_Pos, int &forward);
	inline void getDirectionalOffsets(int& x_Offset, int& y_Offset, int direction);

	inline void printMaze();
private:
	int maze_Width, maze_Height;
	int start_X, start_Y, end_X, end_Y;
	std::vector< std::vector<char> > maze_Board;
};