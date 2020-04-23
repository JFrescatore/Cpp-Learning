#pragma once
#include <iostream>	//Cin/ Cout
#include <string>	//string
#include <time.h>	//Time()
#include <stdlib.h>	//Rand()
#include <thread>	//Sleep()
#include <chrono>	//Seconds()


class TortoiseHare {
public:
	TortoiseHare(int repeat_Time = 1);
	~TortoiseHare();

	void invokeRepeating(int repeat_Time);

	int tortoiseMove(std::string* race);
	int hareMove(std::string* race);
private:
	std::string race_Array[70];
	int race_Length = 70;
	
};