#pragma once

#include "Rule.h"
#include <fstream>

class MonsterManager
{
private:
	std::vector<std::string> Messages;

	std::map<int, Rule> RuleList;

public:

	void SetRulesAndMessages(std::string FileName);

	int GetValidMessNumForRule(int RuleNum);

};