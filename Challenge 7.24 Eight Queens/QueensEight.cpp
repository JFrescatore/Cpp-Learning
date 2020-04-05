#include "QueensEight.h"

using namespace std;

QueensEight::QueensEight(int x_Board, int y_Board) {
	this->x_Board = x_Board;
	this->y_Board = y_Board;
	queens = x_Board;
	board.resize(x_Board * y_Board);
	branch.resize(x_Board);
	for (int i = 0; i < board.size(); i++) {
		board[i] = 1;	//Populate board with an active square
	}
}

QueensEight::~QueensEight() {

}


void QueensEight::handleMoves(int pos, bool active) {
	static vector<int> previous;	//Saves the squares "captured" by the queen
	int x_Pos = -1, y_Pos = -1;	//Pos in board coords
	convertOctalPos(pos, x_Pos, y_Pos);	//Get coords
	int x_Temp = x_Pos;	//Save a temp to preserve original
	int y_Temp = y_Pos;	//Save a temp to preserve original

	if (active) {	//If true
		for (int i = previous.size() - 1; i > -1; i--) {	//Each number saved should be released
			if (previous[i] == -1) {	//If -1 is reached, a branch has ended. Stop
				previous.pop_back();	//Remove
				break;	//Break loop
			}
			board[previous[i]] = 1;	//Release captured square
			previous.pop_back();	//Remove square from saved list
		}
		return;	//End function
	}	//End releasing captured 
	else {
		board[pos] = 0;	//Capture current square
		previous.push_back(-1);	//Create new branch
		previous.push_back(pos);	//Add current square
	}	//End creat new branch
	
	for (int x = -1, y = -1; x < 2;) {	//-1, -1 is the first square order, 1, 1 is the final.
		//Both coords need to be within range to be legal move
		if (x_Temp + x > 0 && x_Temp + x <= x_Board && y_Temp + y > 0 && y_Temp + y <= y_Board) {
			x_Temp += x;	//Step to legal square
			y_Temp += y;	//Step to legal square
			if (board[convertDecimalPos(x_Temp, y_Temp)] == 1) {	//If the square was not already captured, capture
				board[convertDecimalPos(x_Temp, y_Temp)] = 0;	//Reflect capture on board
				previous.push_back(convertDecimalPos(x_Temp, y_Temp));	//Save the captured square to this branch
			}	//End capturing
		}	//End stepping
		else {	//If move is not legal, move to next square sequence.
			if (y >= 1) {	//1 is the max Y can reach, if reached, x increments and reset y
				y = -1;	//Reset y
				x++;	//Y max reached, increment	
			}
			else if (x != 0) {	//If x is not 0, add 1 to y each time an illegal move is made
				y++;	//Y + 1 for when X != 0
			}
			else {	//Add 2, as 0,0 is not a move order
				y += 2;	//Y + 2 for when x does equal 0
			}	//End sequencing

			x_Temp = x_Pos;	//Reset, prep for next square march
			y_Temp = y_Pos;	//Reset, prep for next square march
		}	//Handle change of squares
	}	//End square searching loop
}	//End handleMooves(int, bool)

void QueensEight::createBranch(int pos) {
	if (queens == 0) {	//Check if the game is complete
		readPlacements();	//Give the placements
		return;
	}	//End move print

	int oldPos = pos;	//USed for checking

	for (int i = (current_Branch + 1) * x_Board; i < ((current_Branch + 1) * x_Board) + x_Board; i++) {	//Start pos is the first number in the next branch, end is final
		if (board[i] == 1 && pos != i) {	//If square is open, and not current pos found new square
			pos = i;	//Save square
			current_Branch++;	//Branch has grown
			branch[current_Branch] = pos;	//Store branch
			queens--;	//Queen placed, reduce remaingin queens
			handleMoves(pos);	//Capture squares
			break;
		}	//End found move
	}	//End move finder

	if (oldPos == pos) {	//If pos is equal to oldPos then no new square was found in loop, branch failed
		pos = branchFail(pos);
	}

	createBranch(pos);
	return;
}	//End createBranch(int)

int QueensEight::branchFail(int pos) {
	int oldPos = pos;
	handleMoves(pos, true);	//Release squares from failed placement

	for (int i = pos; i < (current_Branch * x_Board) + x_Board; i++) {	//Search for new squares from previous square to end of branch
		if (board[i] == 1 && i != pos) {	//If square is open, and not current pos found new square
			pos = i;	//Save new square
			branch[current_Branch] = pos;	//Store branch
			handleMoves(pos);	//Capture squares
			return pos;	//End function
		}	//End found move
	}	//End move finder
	//If reached, no new square is found in branch. A critical failure happened, step back and create new branch
	current_Branch--;	//Drop branch down 1
	queens++;	//Pick queen back up
	pos = branch[current_Branch];	//Rever to old branch pos
	branchFail(pos);	//Return pos
}	//End branchFail(int)


void QueensEight::convertOctalPos(int pos, int& x, int& y) {
	int i = 1;

	y = pos % x_Board + 1;	//Find y coord
	while(pos > 0) {
		int remainder = pos % x_Board;	//Base 8, find remainder
		x += remainder * i;	//Add remainder into correct position
		pos /= x_Board;	//Reduce
		i *= 10;	//Increase position
	}	//End conversion 

	x = (x / 10) % 8 + 1;	//Find x coord
}

int QueensEight::convertDecimalPos(int x, int y) {
	int square = (x - 1) * x_Board + (y - 1);
	return square;
}

vector<int> QueensEight::getBoard() {
	return board;
}

void QueensEight::readPlacements() {
	cout << "Root " << current_Branch % 7 << endl;
	int x = 0, y = 0;
	for (int i = 0; i < branch.size(); i++) {
		x = 0;
		y = 0;
		convertOctalPos(branch[i], x, y);
		char x_Character = 96 + x;
		cout << "Queen " << i+1 << ": " << x_Character << y << endl;
	}
	cout << endl;
} //End outputFormated(int, int, int, int)
