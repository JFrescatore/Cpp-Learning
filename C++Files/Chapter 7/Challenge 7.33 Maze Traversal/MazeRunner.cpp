#include "MazeRunner.h"

using namespace std;

MazeRunner::MazeRunner(int maze_Width, int maze_Height) : maze_Width(maze_Width), maze_Height(maze_Height) {
	srand(time(NULL));
	maze_Board.resize(maze_Width);
	buildMaze();
}

MazeRunner::~MazeRunner() {
	
}

void MazeRunner::buildMaze() {
	int start_Remains = 1, end_Remains = 1, rand_Int = 0;
	for (int i = 0; i < maze_Width; i++) {
		vector<char> vertical;	//Build the column
		vertical.resize(maze_Height);
		maze_Board[i] = vertical;	//Add to row
	}	//Build the maze board

	for (int x = 0, y = 0; x < maze_Width; y++) {
		if (y >= maze_Height) {
			y = 0;	//Reset y, y max reached
			x++;	//Increase x
			if (x >= maze_Width)	//End loop if x is max 
				break;	//Exit loop
		}	//In loop controller

		if (y == 0 || y == maze_Height - 1) {
			maze_Board[x][y] = '#';	//Store wall
			continue;	//Loop back from here
		}	//If Y is top or bottom, its automaically a wall

		int rand_Int = rand() % maze_Width * 0.45f + 1;	//Prep random num for end/start placement
		
		if (x == 0) {
			if (start_Remains * (rand_Int + y) > maze_Width * 0.55f) {
				start_Remains = 0;	//Reduce starts remaining
				maze_Board[x][y] = 'X';	//Place computer 
				start_X = x; start_Y = y;	//Save start position
				continue;	//Loop back from here
			}	//End if start
			else {
				maze_Board[x][y] = '#';	//Place wall if not start
				continue;	//Loop back from here
			}	//End column 0 populating
		}	//End column 0
		else if (x == maze_Width - 1) {
			if (end_Remains * (rand_Int + y) > maze_Width * 0.55f) {
				end_Remains = 0;	//Reduce end points
				maze_Board[x][y] = '.';	//Place end indicator
				end_X = x; end_Y = y;	//Save end posiiton
				continue;	//Loop back from here
			}	//End if end
			else {
				maze_Board[x][y] = '#';	//Place wall if not end
				continue;	//Loop back from here
			}	//End column last populating
		}	//End column last
		else {
			rand_Int = rand() % 100 + 1;	//Decide if empty pos is a wall or not
			if(rand_Int <= 30)	//30% chance to be a wall
				maze_Board[x][y] = '#';	//place wall
			else
				maze_Board[x][y] = '.';	//Place empty
		}	//End population
	}	//End populate maze
	printMaze();
	mazeTraverse(start_X, start_Y, 0);
}	//End buildMaze();

/*
Procedure: if (start_Remains * (rand_Int + y) > maze_Width * 0.55f) the start or end has been found
There is a 30% chance for a wall to form anywhere within the maze
*/

void MazeRunner::mazeTraverse(int x_Position, int y_Position, int forward) {
	maze_Board[x_Position][y_Position] = 'X';	//Update position with X marker

	int x_Next = x_Position, y_Next = y_Position, forward_Next = forward;	//Create temp variables
	
	if (x_Position == end_X && y_Position == end_Y) {	//IF computer position reached end positions, it has finished the maze
		cout << "End Reached! Maze finished." << endl;
		return;	//End recursion
	}	//End Win conditions

	cout << "Current: " << forward << "|" << x_Position + 1 << "," << y_Position + 1 << endl;	//Give information about position, and direction

	lookDirection(x_Next, y_Next, forward_Next);	//Look for future move
	
	if (x_Next != x_Position || y_Next != y_Position)
		maze_Board[x_Position][y_Position] = '.';	//Update old position to be empty
	else
		return;	//End recursion
	//End updating maze/Lose condition
	
	cout << "Looking in Direction: " << forward_Next << "|" << x_Next + 1 << "," << y_Next + 1 << endl;	//Give information about next move, and direction

	printMaze();	//Print maze with updated info
	mazeTraverse(x_Next, y_Next, forward_Next);	//Move to next position
	return;	//End recursion
}

void MazeRunner::lookDirection(int& x_Pos, int& y_Pos, int& forward) {
	int direction = forward + 1;	//Looks at right
	int x_Offset, y_Offset;
	while (true) {
		if (direction < 0)
			direction = 3;
		else if (direction > 3)
			direction = 0;	
		//End control of direction

		getDirectionalOffsets(x_Offset, y_Offset, direction);	//Get move directions
		if (maze_Board[x_Pos + x_Offset][y_Pos + y_Offset] == '#') {
			if (x_Pos == start_X) {
				cout << "Stuck. Maze not possible. " << endl;
				break;
			}	//If the computer is at the start position, and a wall is found right, it is blocking exit. Break
			direction--;
			continue;
		}
		else {
			x_Pos += x_Offset; y_Pos += y_Offset;	//Modify position, and save it
			maze_Board[x_Pos][y_Pos] = 'X';
			forward = direction;	//Update forward
			break;	//Exit
		}	//End Checking Right
	}	//End Checking movement
}	//End lookDirection(int&, int&, int&)

inline void MazeRunner::getDirectionalOffsets(int& x_Offset, int& y_Offset, int direction) {
	switch (direction) {
		case 0:
			x_Offset = 0; y_Offset = -1;
			break;
		case 1:
			x_Offset = 1; y_Offset = 0;
			break;
		case 2:
			x_Offset = 0; y_Offset = 1;
			break;
		case 3:
			x_Offset = -1; y_Offset = 0;
			break;
	}	//Directional offset, used to "rotate"
}	//End getDirectionalOffsets(int&, int&, int)
/*
								Procedure:
							|----1: Check Right for wall----|
							|				|
							|				|
					|----2.a: If wall, check forwad----|	2.b: If empty, move right. Restart	
					|			  	   |
					|				   |
			|----3.Z: If blocked, look left----|	3.b: If clear, advance forward. Restart		
			|				   |
			|				   |
      4.a: If clear, advance left. Restart	4.b: If blocked advance back. Restart


***Failure Condition: If forward direction is [3] while on start position, failure.*** 
***Win Condition: computer reaches the exit position

Each time the computer advances, the "forward" becomes the direction it turned.
EX: Forward is up [0, 1], right is [1, 0]. If computer advances to the right then forward is now [1, 0] and right becomes [0, -1]

<Direction>[Coords][Short Hand]

		Up [0, 1][2]
Left [-1, 0][3]	 	.	Right [1, 0][1]
		Down [0, -1][0]
*/

inline void MazeRunner::printMaze() {
	for (int x = 0, y = 0; y < maze_Height; x++) {
		if (x == maze_Width) {
			x = 0;
			y++;
			cout << endl;
			if (y == maze_Height)
				break;
		}	//End controls

		cout << maze_Board[x][y] << "  ";
	}
	cout << endl << endl;
}	//End printMaze
