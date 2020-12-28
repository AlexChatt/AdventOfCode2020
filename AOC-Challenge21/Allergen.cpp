#include "Allergen.h"

void Allergen::SetPotentialIngrediants(std::string NewIngrediant)
{
	PotentialIngrediants.insert(NewIngrediant);
}