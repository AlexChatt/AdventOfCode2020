#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include "Rule.h"

class Train
{
private:
	std::vector<Rule> RuleList;

	std::vector<int> MyTicketNumbers;
	std::vector<std::vector<int>> NearbyTicketNumbers;


public:

	void GetTicketandRules(const std::string FileName);
	int GetTotalErrorRate();

	void GetCorrectIndexPerRule();
	void SetLockedIndex();

	uint64_t GetDepartureTotal();
};