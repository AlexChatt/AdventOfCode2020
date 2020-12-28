#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "Food.h"

class FoodList
{
private:

	std::map<std::string, std::vector<Food>> AllergensFoodMap;
	std::map<std::string, int> Ingrediants;

	std::set<std::string> NoAllergensIngrediants;

	std::map<std::string, std::string> AllergenMap;

	void UpdateFoodListAllergen();
	bool AreAllAllergenIngrediantsFound();

	bool CheckIngrediantInAll(std::string Ingrediant, std::string AllergenType);
	bool IsAllergenIngrediantTaken(std::string Ingrediant);
	bool IsIngrediantInAnyOfAllOthers(std::string Ingrediant, std::string CurrentAl);

public:

	bool SetUpFoodList(const std::string FileName);

	uint16_t NonAllergensCount();

	std::map<std::string, std::string> GetAllergenList();

};