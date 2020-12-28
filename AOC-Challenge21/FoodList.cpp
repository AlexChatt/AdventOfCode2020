#include "FoodList.h"

bool FoodList::SetUpFoodList(const std::string FileName)
{
	std::ifstream File(FileName);
	if (!File)
	{
		std::cout << "Could not find file " << FileName << std::endl;
		return false;
	}

	Food NewFood;
	std::string templine;

	while (std::getline(File, templine))
	{
		std::istringstream iss(templine);
		std::string word;
		while (std::getline(iss, word, ' '))
		{
			if (word.find('(') == std::string::npos)
			{
				NewFood.Ingrediants.push_back(word);
				if (Ingrediants.count(word))
				{
					Ingrediants[word]++;
				}
				else
				{
					Ingrediants[word] = 1;
				}
			}
			else
			{
				std::size_t AlStart = templine.find("(contains ") + std::string("(contains ").size();
				std::size_t AlEnd = templine.find(")");
				std::string AllergensList = templine.substr(AlStart, AlEnd - AlStart);

				std::istringstream iss2(AllergensList);
				std::string Allergen;
				while (std::getline(iss2, Allergen, ','))
				{
					Allergen.erase(std::remove_if(Allergen.begin(), Allergen.end(), std::isspace), Allergen.end());
					AllergensFoodMap[Allergen].push_back(NewFood);
					AllergenMap[Allergen] = "";
				}
				break;
			}
		}
		NewFood.Ingrediants.clear();
	}

	return true;
}

uint16_t FoodList::NonAllergensCount()
{
	uint16_t NoAllCount = 0;

	std::map <std::string, int>::iterator IngMapit;
	std::map<std::string, std::vector<Food>>::iterator Mapit;

	bool AmIInAll = true;
	int InAllCount = 0;

	for(IngMapit = Ingrediants.begin(); IngMapit != Ingrediants.end(); IngMapit++)
	{
		InAllCount = 0;

		for (Mapit = AllergensFoodMap.begin(); Mapit != AllergensFoodMap.end(); ++Mapit)
		{
			AmIInAll = true;

			for (int i = 0; i < Mapit->second.size(); i++)
			{
				if (!Mapit->second[i].DoIngrediantsContain(IngMapit->first))
				{
					AmIInAll = false;
					break;
				}
			}

			if (AmIInAll)
			{
				InAllCount++;
				break;
			}
		}

		if (InAllCount == 0)
		{
			NoAllergensIngrediants.insert(IngMapit->first);
		}
	}

	std::set<std::string>::iterator setit;
	for (setit = NoAllergensIngrediants.begin(); setit != NoAllergensIngrediants.end(); setit++)
	{
		NoAllCount += Ingrediants[*setit];
	}

	return NoAllCount;

}


std::map<std::string, std::string> FoodList::GetAllergenList()
{
	std::map<std::string, std::string>::iterator Mapit;
	std::vector<std::string>::iterator Ingrediant;

	bool BadStuffHappen = false;
	UpdateFoodListAllergen();

	while (!AreAllAllergenIngrediantsFound() && !BadStuffHappen)
	{
		for (Mapit = AllergenMap.begin(); Mapit != AllergenMap.end(); ++Mapit)
		{
			if (Mapit->second != "") { continue; }
			if (AllergensFoodMap[Mapit->first].size() == 0) 
			{ 
				BadStuffHappen = true;
				break;
			}

			std::vector<std::string> PossibleAI = AllergensFoodMap[Mapit->first][0].PossibleAllergensFoods;

			for (Ingrediant = PossibleAI.begin(); Ingrediant != PossibleAI.end(); ++Ingrediant)
			{
				if (CheckIngrediantInAll(*Ingrediant, Mapit->first) && 
					!IsAllergenIngrediantTaken(*Ingrediant))
				{
					if (!IsIngrediantInAnyOfAllOthers(*Ingrediant, Mapit->first))
					{
						AllergenMap[Mapit->first] = *Ingrediant;
						break;
					}
				}
			}
		}
	}

	return AllergenMap;
}

void FoodList::UpdateFoodListAllergen()
{
	std::map<std::string, std::vector<Food>>::iterator Mapit;

	for (Mapit = AllergensFoodMap.begin(); Mapit != AllergensFoodMap.end(); ++Mapit)
	{
		for (int i = 0; i < Mapit->second.size(); i++)
		{
			Mapit->second[i].SetupPossibleAllergenIngred(NoAllergensIngrediants);
		}
	}
}

bool FoodList::AreAllAllergenIngrediantsFound()
{
	std::map<std::string, std::string>::iterator Mapit;

	for (Mapit = AllergenMap.begin(); Mapit != AllergenMap.end(); ++Mapit)
	{
		if (Mapit->second == "")
		{
			return false;
		}
	}

	return true;
}

bool FoodList::CheckIngrediantInAll(std::string Ingrediant, std::string AllergenType)
{
	std::vector<Food> FoodsForAllergen = AllergensFoodMap[AllergenType];

	for (int i = 0; i < FoodsForAllergen.size(); i++)
	{
		if (!FoodsForAllergen[i].DoPossibleAllergensContain(Ingrediant))
		{
			return false;
		}
	}

	return true;
}

bool FoodList::IsAllergenIngrediantTaken(std::string Ingrediant)
{
	std::map<std::string, std::string>::iterator Mapit;

	for (Mapit = AllergenMap.begin(); Mapit != AllergenMap.end(); ++Mapit)
	{
		if (Mapit->second == Ingrediant)
		{
			return true;
		}
	}

	return false;
}

bool FoodList::IsIngrediantInAnyOfAllOthers(std::string Ingrediant, std::string CurrentAl)
{
	std::map<std::string, std::vector<Food>>::iterator Mapit;

	for (Mapit = AllergensFoodMap.begin(); Mapit != AllergensFoodMap.end(); ++Mapit)
	{
		if (Mapit->first == CurrentAl) { continue; }

		bool InAll = true;

		for (int i = 0; i < Mapit->second.size(); i++)
		{
			if (!Mapit->second[i].DoPossibleAllergensContain(Ingrediant))
			{
				InAll = false;
				break;
			}
		}

		if (InAll && AllergenMap[Mapit->first] == "")
		{
			return true;
		}
	}

	return false;
}