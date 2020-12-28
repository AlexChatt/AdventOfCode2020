#pragma once

#include <vector>
#include <string>
#include <set>

struct Food
{
public:
	std::vector<std::string> Ingrediants;

	bool DoIngrediantsContain(std::string Ingrediant);
};