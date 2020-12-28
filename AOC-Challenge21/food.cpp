#include "Food.h"

bool Food::DoIngrediantsContain(std::string Ingrediant)
{
	for (std::vector<std::string>::iterator it = Ingrediants.begin(); it != Ingrediants.end(); ++it)
	{
		if (*it == Ingrediant)
		{
			return true;
		}
	}

	return false;
}


void Food::SetupPossibleAllergenIngred(std::set<std::string> NonAllergensFoods)
{
	for (std::vector<std::string>::iterator it = Ingrediants.begin(); it != Ingrediants.end(); ++it)
	{
		if (!NonAllergensFoods.count(*it))
		{
			PossibleAllergensFoods.push_back(*it);
		}
	}
}

bool Food::DoPossibleAllergensContain(std::string Ingrediant)
{
	for (std::vector<std::string>::iterator it = PossibleAllergensFoods.begin(); it != PossibleAllergensFoods.end(); ++it)
	{
		if (*it == Ingrediant)
		{
			return true;
		}
	}

	return false;
}