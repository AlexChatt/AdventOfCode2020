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

	std::map<std::string, std::vector<Food>> AllergensMap;
	std::map<std::string, int> Ingrediants;

	std::set<std::string> NoAllergensIngrediants;

	void UpdateFoodListAllergen();

	bool CheckIngrediantInAll(std::string Ingrediant, std::string AllergenType);

public:

	bool SetUpFoodList(const std::string FileName);

	uint16_t NonAllergensCount();

	std::map<std::string, std::string> GetAllergenList();

};