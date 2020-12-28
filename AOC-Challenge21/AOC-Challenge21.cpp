#include "FoodList.h"

int main()
{
	FoodList MyFoodList;
   
	if(!MyFoodList.SetUpFoodList("input.txt"))
	{
		return -1;
	}

	std::cout<< "P1: Answer = " << MyFoodList.NonAllergensCount() << std::endl;

	std::map<std::string, std::string> Allergens = MyFoodList.GetAllergenList();

	std::map<std::string, std::string>::iterator Mapit;
	for (Mapit = Allergens.begin(); Mapit != Allergens.end(); ++Mapit)
	{
		std::cout << Mapit->second;
		if (++Mapit != Allergens.end())
		{
			std::cout << ",";
		}
		--Mapit;
	}

}
