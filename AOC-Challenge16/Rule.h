#pragma once

#include <string>
#include <vector>

class Rule
{
private:
	std::string name;
	int FirstMin, FirstMax;
	int SecondMin, SecondMax;

	std::vector<int> PossibleTicketIndex;
	int TicketIndexPos = -1;

public:
	Rule(std::string rulename);

	void SetFirstRange(int FMin, int FMax);
	void SetSecondRange(int SMin, int SMax);
	void SetRuleIndexForTicket(int Index);
	void AddPossibleTicketIndex(int Index);
	void RemovePossibleIndex(int Index);

	bool DoesNumberFitInRule(int number);

	std::string GetName()
	{
		return name;
	}
	int GetRuleTicketIndex()
	{
		return TicketIndexPos;
	}
	std::vector<int> GetPossibleIndex()
	{
		return PossibleTicketIndex;
	}
};