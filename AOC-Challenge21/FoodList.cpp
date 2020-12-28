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
					AllergensMap[Allergen].push_back(NewFood);
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

		for (Mapit = AllergensMap.begin(); Mapit != AllergensMap.end(); ++Mapit)
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
	std::map<std::string, std::vector<Food>>::iterator Mapit;

	for (Mapit = AllergensMap.begin(); Mapit != AllergensMap.end(); ++Mapit)
	{
		CreateAllergenFoods(Mapit->first);
	}



	//return AllergenMap;
}

void FoodList::CreateAllergenFoods(std::string AllergenName)
{
	Allergen NewAllergen;
	NewAllergen.Name = AllergenName;

	//for()

}

bool FoodList::CheckIngrediantInAll(std::string Ingrediant, std::string AllergenType)
{

}
