#include "Rule.h"

Rule::Rule(std::string rulename)
{
	name = rulename;
}

void Rule::SetFirstRange(int FMin, int FMax)
{
	FirstMin = FMin;
	FirstMax = FMax;
}

void Rule::SetSecondRange(int SMin, int SMax)
{
	SecondMin = SMin;
	SecondMax = SMax;
}

void Rule::SetRuleIndexForTicket(int Index)
{
	TicketIndexPos = Index;
}

void Rule::AddPossibleTicketIndex(int Index)
{
	PossibleTicketIndex.push_back(Index);
}

void Rule::RemovePossibleIndex(int Index)
{
	for (int i = 0; i < PossibleTicketIndex.size(); i++)
	{
		if (PossibleTicketIndex[i] == Index)
		{
			PossibleTicketIndex.erase(PossibleTicketIndex.begin() + i);
			break;
		}
	}
}

bool Rule::DoesNumberFitInRule(int number)
{
	if ((number >= FirstMin && number <= FirstMax) || (number >= SecondMin && number <= SecondMax))
	{
		return true;
	}
	return false;
}
