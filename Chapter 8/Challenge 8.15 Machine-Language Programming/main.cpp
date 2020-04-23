#include <iostream>

using namespace std;

void sentinelControlledLoop(int* _memory);
void counterControlledLoop(int* _memory);
void largestNumber(int* _memory);
void operationCodes(int* _memory, int* _accumulator, int* _memory_position, int _command);

int main() {
	int memory[100] = {};
	int accumulator = 0;
	int i = 0;

	
	
	while (true) {
		sentinelControlledLoop(memory);
		cout << ">> First Program:\n>> Continue entering positive numbers, each time you enter that number will be added to a sum of all numbers."
			<< "\n>> If a negative number is entered that program will end and the next one will begin." << endl;
		while (accumulator != -2147483647) {
			operationCodes(memory, &accumulator, &i, memory[i]);
			i++;
		}
		accumulator = 0;
		i = 0;
		counterControlledLoop(memory);
		cout << ">> Second Program:\n>> Enter 7 numbers, once 7 numbers have been entered the program will then find the average of the 7 numbers." << endl;
		while (accumulator != -2147483647) {
			operationCodes(memory, &accumulator, &i, memory[i]);
			i++;
		}
		accumulator = 0;
		i = 0;
		largestNumber(memory);
		cout << ">> Third Program:\n>> Enter a number, this number will be how many numbers will be entered."
			<< "\n>> Once the amount of numbers entered is equal to the first number the program will tell you the largest number entered." << endl;
		while (accumulator != -2147483647) {
			operationCodes(memory, &accumulator, &i, memory[i]);
			i++;
		}
		break;
	}

	cout << "All Programs Ended." << endl;
	cin.get();
	return 0;
}

/*TEST
	Input 1, twice. then Input -1
*/

void sentinelControlledLoop(int* _memory) {
	_memory[0] = +1012;	//Read first number
	_memory[1] = +2012;	//Load first number
	_memory[2] = +4111;	//Check if negative, if negative branch to memory 11

	_memory[3] = +1013;	//Read second number
	_memory[4] = +2013;	//Load second number
	_memory[5] = +4111;	//Check if negative, if negative branch to memory 11

	_memory[6] = +2012;	//Load first number
	_memory[7] = +3013;	//Add second to first
	_memory[8] = +2112;	//Store at first number registry
	_memory[9] = +1112;	//Write to screen
	_memory[10] = +4003;	//Restart loop at memory 3, continue adding until negative

	_memory[11] = +4300;	//Return kill signal, Halt

	_memory[12] = +0000;	//Store variable A
	_memory[13] = +0000;	//Store variable B
}

/*TEST
	Input 1 each time. The final output should be 1.

*/

void counterControlledLoop(int* _memory) {
	_memory[0] = +1015;	//Read input to numA variable
	_memory[1] = +2016;	//Load sum variable
	_memory[2] = +3015;	//Add numA to sum
	_memory[3] = +2116;	//Store new sum

	_memory[4] = +2017;	//Load counter
	_memory[5] = +3018;	//Increment counter by variable of increment_amount
	_memory[6] = +2117;	//Store increment
	_memory[7] = +3119;	//Subtract current counter by needed amount
	_memory[8] = +4210;	//If current accumulator is equal to 0, branch to next step
	_memory[9] = +4000;	//Restart loop

	_memory[10] = +2016;	//Load sum
	_memory[11] = +3219;	//Divide sum by population amount for average
	_memory[12] = +2120;	//Store result in average variable
	_memory[13] = +1120;	//Write average to screen
	_memory[14] = +4300;	//Return kill singal, Halt

	_memory[15] = +0000;	//Store input number variable
	_memory[16] = +0000;	//Store Sum variable
	_memory[17] = +0000;	//Store counter variable
	_memory[18] = +0001;	//Store increment amount variable
	_memory[19] = +0007;	//Store sentinel variable
	_memory[20] = +0000;	//Store average variable
}

/*TEST
	Input Number 5. Then enter 1, 1, 1, 1, 4
	Output should be 4
*/

void largestNumber(int* _memory) {
	_memory[0] = +1020;	//Read input to max variable
	_memory[1] = +1016;	//Read input to numA
	_memory[2] = +2017;	//Load largest num
	_memory[3] = +3116;	//Subtract numA from largest
	_memory[4] = +4111;	//If negative, numA is larger

	_memory[5] = +2018;	//Load counter
	_memory[6] = +3019;	//Add increment
	_memory[7] = +2118;	//Store counter
	_memory[8] = +3120;	//Subtract max from counter
	_memory[9] = +4214;	//If 0, loop completed branch to end
	_memory[10] = +4001;	//Branch to start to continue loop

	_memory[11] = +2016;	//Load numA
	_memory[12] = +2117;	//Store numA as largest
	_memory[13] = +4005;	//Branch to load counter

	_memory[14] = +1117;	//Write largest to screen
	_memory[15] = +4300;	//halt

	_memory[16] = +0000;	//Store numA variable
	_memory[17] = +0000;	//Store largest number variable
	_memory[18] = +0000;	//Store counter variable
	_memory[19] = +0001;	//Store increment amount variable
	_memory[20] = +0000;	//Store max loop variable
}

void operationCodes(int* _memory, int* _accumulator, int* _memory_position, int _command) {
	switch (_command / 100) {
/*Read Write Operations*/
	case 10:	//Read command, read from keyboard storing the number
		std::cin >> _memory[_command % 100];
		break;
	case 11:	//Write command, write the word stored in the given registry to screen
		std::cout << ">> " << _memory[_command % 100] << std::endl;
		break;
/*Load Store Operations*/
	case 20:	//Load command, load word from registry to accumulator
		*_accumulator = _memory[_command % 100];
		break;
	case 21:	//Store command, store the word in teh accumulator to the given registry
		_memory[_command % 100] = *_accumulator;
		break;
/*Arthmetic Operations*/
	case 30:	//Add command, add the word from the given registry to the accumulator
		*_accumulator += _memory[_command % 100];
		break;
	case 31:	//Subtract command, subtract the word in the given registry from the accumulator
		*_accumulator -= _memory[_command % 100];
		break;
	case 32:	//Divide command, divide the word in the given registry from the accumulator
		*_accumulator /= _memory[_command % 100];
		break;
	case 33:	//Multiply command, multiply the word in the given registry with the accumulator
		*_accumulator *= _memory[_command % 100];
		break;
/*Transfer-Of-Control Operations*/
	case 40:	//Bracnh, Branch to given memory
		*_memory_position = _command % 100;
		operationCodes(_memory, _accumulator, _memory_position, _memory[_command % 100]);
		break;
	case 41:	//BranchNeg, branch to specifc location in memory if accumulator is negative
		if (*_accumulator < 0) {
			*_memory_position = _command % 100;
			operationCodes(_memory, _accumulator, _memory_position, _memory[_command % 100]);
		}
		break;
	case 42:	//BranchZero, branch to specific location in memory if accumulator is zero
		if (*_accumulator == 0) {
			*_memory_position = _command % 100;
			operationCodes(_memory, _accumulator, _memory_position, _memory[_command % 100]);
		}
		break;
	case 43:	//Halt, stop the program
		*_accumulator = -2147483647;
		break;
/*C++ Failsafe*/
	default:	//Incase no proper command was added
		std::cout << "ERROR: Command Not Recognized" << std::endl;
		break;
	}
}