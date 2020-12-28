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
