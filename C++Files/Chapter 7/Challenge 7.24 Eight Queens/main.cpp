#include "QueensEight.h"
#include <cstdio>

using namespace std;

int main() {
	QueensEight queensEight;
	
	queensEight.createBranch(-1);
	int x = 0, y = 0;
	queensEight.convertOctalPos(46, x, y);
	cout << x << "," << y << endl;
	/*
	for (int i = 0; i < queensEight.getBoard().size(); i++) {
		if (i % 8 == 0) {
			cout << "\nBranch " << i / 8 << endl;
			cout << "	Squares In Branch" << endl;
		}
		cout << "Square: " << i << "		Active: " << queensEight.getBoard()[i] << endl;
	}
	*/
	getchar();
	return 0;
}
