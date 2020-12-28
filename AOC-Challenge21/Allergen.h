#pragma once

#include <string>
#include <set>

struct Allergen
{
	std::string Name;
	std::set<std::string> PotentialIngrediants;
	std::string AllergenIngrediants;


	void SetPotentialIngrediants(std::string NewIngrediant);
};