// AOC-Challenge19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MonsterMessages.h"

int main()
{
	MonsterManager MessageRuleChecker;

	MessageRuleChecker.SetRulesAndMessages("input.txt");

	std::cout<< "P1 Valid Messages Count: " << MessageRuleChecker.GetValidMessNumForRule(0) << std::endl;
   
	return 0;
}
