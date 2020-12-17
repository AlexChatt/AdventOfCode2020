#pragma once

#include <vector>
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
	
	uint64_t GetDepartureMultiTotal();

};