#pragma once

#include <vector>
#include <string>
#include <set>

struct Food
{
public:
	std::vector<std::string> Ingrediants;

	std::vector<std::string> PossibleAllergensFoods;

	bool DoIngrediantsContain(std::string Ingrediant);
	void SetupPossibleAllergenIngred(std::set<std::string> NonAllergensFoods);
	bool DoPossibleAllergensContain(std::string Ingrediant);
};