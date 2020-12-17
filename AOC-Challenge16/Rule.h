#pragma once

#include <string>

class Rule
{
private:
	std::string name;
	int FirstMin, FirstMax;
	int SecondMin, SecondMax;

public:
	Rule(std::string rulename);

	void SetFirstRange(int FMin, int FMax);
	void SetSecondRange(int SMin, int SMax);

	bool DoesNumberFitInRule(int number);

};