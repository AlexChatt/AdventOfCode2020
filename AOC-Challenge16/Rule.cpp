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

bool Rule::DoesNumberFitInRule(int number)
{
	if ((number >= FirstMin && number <= FirstMax) || (number >= SecondMin && number <= SecondMax))
	{
		return true;
	}
	return false;
}