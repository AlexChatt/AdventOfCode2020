// AOC-Challenge16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Train.h"

int main()
{
	Train MainTrain;
	MainTrain.GetTicketandRules("input.txt");

	std::cout << "P1: Ticket scanning error rate " << MainTrain.GetTotalErrorRate() << std::endl;
 
	return 0;
}
