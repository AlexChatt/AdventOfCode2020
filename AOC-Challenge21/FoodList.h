#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "Food.h"
#include "Allergen.h"

class FoodList
{
private:

	std::map<std::string, std::vector<Food>> AllergensMap;
	std::map<std::string, int> Ingrediants;

	std::set<std::string> NoAllergensIngrediants;

	std::map<std::string, Allergen> AllergenIngerMap;

	void CreateAllergenFoods(std::string AllergenName);

	bool CheckIngrediantInAll(std::string Ingrediant, std::string AllergenType);

public:

	bool SetUpFoodList(const std::string FileName);

	uint16_t NonAllergensCount();

	std::map<std::string, std::string> GetAllergenList();

};