#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>

struct RuleCombo
{
	std::vector<int> RuleList;
};

class Rule
{
private:

	int RuleNumber;

	std::vector<RuleCombo> PossibleComboRules;

	std::vector<std::string> ComboStringList;

	void SetRuleNum(int RNum);

	void GetCombos1Rules(std::vector<std::vector<std::string>> VectorOfStringCombos);
	void GetCombos2Rules(std::vector<std::vector<std::string>> VectorOfStringCombos);
	void GetCombos3Rules(std::vector<std::vector<std::string>> VectorOfStringCombos);

public:

	void SetInfo(std::string RulesCombo);
	
	void WorkOutStringCombos(std::map<int,Rule> RuleList);

	int GetValidMessagesNum(std::vector<std::string> Messages, std::map<int, Rule> RuleList);

	int GetRuleNum();

	std::vector<std::string> GetComboList();
};