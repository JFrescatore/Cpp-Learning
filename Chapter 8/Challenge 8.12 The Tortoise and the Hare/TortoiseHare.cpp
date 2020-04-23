#include "TortoiseHare.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

TortoiseHare::TortoiseHare(int repeat_Time) {
	srand(time(NULL));

	for (int i = 0; i < race_Length; i++)
		race_Array[i] = ".";

	cout << "BANG!" << endl;
	cout << "AND THEYRE OFF!" << endl;
	invokeRepeating(repeat_Time);
}

TortoiseHare::~TortoiseHare() {

}

void TortoiseHare::invokeRepeating(int repeat_Time) {
	int tortoise_Pos = 0, hare_Pos = 0;

	tortoise_Pos = tortoiseMove(race_Array);	//Get tortoise position
	hare_Pos = hareMove(race_Array);	//Get hare positoin

	if (tortoise_Pos == hare_Pos)
		race_Array[tortoise_Pos] = "OUCH!";	//If both are in teh same place, have ouch explain this

	for (int i = 0; i < race_Length; i++)
		cout << race_Array[i];	//Print out all positions
	cout << endl;	//Return line once done

	if (tortoise_Pos >= race_Length - 1 && hare_Pos < race_Length - 1) {	//Tortoise is at end, while hare is not
		cout << "TORTOISE WINS!!!" << endl;
		return;
	}
	else if (tortoise_Pos < race_Length - 1 && hare_Pos >= race_Length - 1) {	//Hare is at end while tortoise is not
		cout << "Yuch (Hare Won)" << endl;
		return;
	}
	else if(tortoise_Pos >= race_Length - 1 && hare_Pos >= race_Length - 1) {
		cout << "Tie?" << endl;	//Both reached end.
		return;
	}

	sleep_for(seconds(repeat_Time));	//Wait 1 second for the tick
	invokeRepeating(repeat_Time);	//No winner, function was not returend before this point, call again
	return;
}

/*	Moves:
	1-5: Big Plod: Plus 3
	6-7: Slip: Minus 6
	8-10: Small Plod: Plus 1
*/
int TortoiseHare::tortoiseMove(string* race) {
	static int position = 0;	//Static to save position
	int move_Type = rand() % 10 + 1;	//Peck random move

	race[position] = ".";	//Empty previous position

	if (move_Type <= 5)
		position += 3;	//Big plod
	else if (move_Type > 5 && move_Type <= 7)
		position -= 6;	//Slip
	else
		position += 1;	//Small plod

	if (position >= race_Length)
		position = race_Length - 1;	//Keep position within max range
	else if (position < 0)
		position = 0;	//Keep positoin within least range

	race[position] = "T";	//Update array with position

	return position;	//Return position for comparing later
}

/*	Moves:
	1-2: Sleep: Nothing
	3-4: Big Hop: Plus 9
	5-5: Big Slip: Minus 12
	6-8: Small Hop: Plus 1
	9-10: Small Slip: Minus 2
*/
int TortoiseHare::hareMove(string* race) {
	static int position = 0;	//Static to save position
	int move_Type = rand() % 10 + 1;

	race[position] = ".";		//Empty previous position

	if (move_Type > 2 && move_Type <= 4) {
		position += 9;	//Big Hop
	}
	else if (move_Type > 4 && move_Type <= 5) {
		position -= 12;	//Big Slip
	}
	else if (move_Type > 5 && move_Type <= 8) {
		position += 1;	//Small Hop
	}
	else {
		position -= 2;	//Small Slip
	}

	if (position >= race_Length)	//Kep position within max range
		position = race_Length - 1;
	else if (position < 0)	//Keep posiotin with least range
		position = 0;

	race[position] = "H";	//Update position on array

	return position;	//Return position for comparing later
}