#include "Rule.h"

void Rule::SetRuleNum(int RNum)
{
	RuleNumber = RNum;
}

void Rule::GetCombos1Rules(std::vector<std::vector<std::string>> VectorOfStringCombos)
{
	for (int n1 = 0; n1 < VectorOfStringCombos[0].size(); n1++)
	{
		ComboStringList.push_back(VectorOfStringCombos[0][n1]);
	}
}

void Rule::GetCombos2Rules(std::vector<std::vector<std::string>> VectorOfStringCombos)
{
	for (int n1 = 0; n1 < VectorOfStringCombos[0].size(); n1++)
	{
		for (int n2 = 0; n2 < VectorOfStringCombos[1].size(); n2++)
		{
			ComboStringList.push_back(VectorOfStringCombos[0][n1] + VectorOfStringCombos[1][n2]);
		}
	}
}

void Rule::GetCombos3Rules(std::vector<std::vector<std::string>> VectorOfStringCombos)
{
	for (int n1 = 0; n1 < VectorOfStringCombos[0].size(); n1++)
	{
		for (int n2 = 0; n2 < VectorOfStringCombos[1].size(); n2++)
		{
			for (int n3 = 0; n3 < VectorOfStringCombos[2].size(); n3++)
			{
				ComboStringList.push_back(VectorOfStringCombos[0][n1] + VectorOfStringCombos[1][n2] + VectorOfStringCombos[2][n3]);
			}
		}
	}
}

void Rule::SetInfo(std::string RulesCombo)
{
	std::size_t colonPos = RulesCombo.find(":");

	SetRuleNum(std::stoi(RulesCombo.substr(0, colonPos)));

	if (RulesCombo.find('"') != std::string::npos)
	{
		ComboStringList.push_back(RulesCombo.substr(RulesCombo.find('"')+1, 1));
	}
	else
	{
		std::size_t PostRuleNum = RulesCombo.find(':');
		std::size_t OrSelection = RulesCombo.find('|');

		if (OrSelection != std::string::npos)
		{
			std::string FirstRule = RulesCombo.substr(PostRuleNum + 2, OrSelection-1 - (PostRuleNum + 2));
			std::string SecondRule = RulesCombo.substr(OrSelection + 2, RulesCombo.size() - (OrSelection + 2));
			
			std::istringstream ss(FirstRule);
			std::string temp;
			RuleCombo NewCombo;
			while (std::getline(ss, temp, ' '))
			{
				NewCombo.RuleList.push_back(std::stoi(temp));
			}
			PossibleComboRules.push_back(NewCombo);
			NewCombo.RuleList.clear();

			std::istringstream ss2(SecondRule);
			while (std::getline(ss2, temp, ' '))
			{
				NewCombo.RuleList.push_back(std::stoi(temp));
			}
			PossibleComboRules.push_back(NewCombo);
		}
		else
		{
			std::string RuleString = RulesCombo.substr(PostRuleNum + 2, RulesCombo.size() - (PostRuleNum + 2));
			std::istringstream ss(RuleString);
			std::string temp;
			RuleCombo NewCombo;
			while (std::getline(ss, temp, ' '))
			{
				NewCombo.RuleList.push_back(std::stoi(temp));
			}
			PossibleComboRules.push_back(NewCombo);
		}
	}

}

void Rule::WorkOutStringCombos(std::map<int, Rule> RuleList)
{
	if (ComboStringList.size() == 0)
	{
		for (int i = 0; i < PossibleComboRules.size(); i++)
		{
			for (int j = 0; j < PossibleComboRules[i].RuleList.size(); j++)
			{
				if (RuleList[PossibleComboRules[i].RuleList[j]].GetComboList().size() == 0)
				{
					if (PossibleComboRules[i].RuleList[j] == RuleNumber)
					{
						int memes = 1;
					}
					RuleList[PossibleComboRules[i].RuleList[j]].WorkOutStringCombos(RuleList);
				}
			}
		}
	}

	for (int i = 0; i < PossibleComboRules.size(); i++)
	{
		std::vector<std::vector<std::string>> VectorOfStringCombos;

		for (int j = 0; j < PossibleComboRules[i].RuleList.size(); j++)
		{
			std::vector<std::string> StringCombos = RuleList[PossibleComboRules[i].RuleList[j]].GetComboList();

			VectorOfStringCombos.push_back(StringCombos);
		}

		if (VectorOfStringCombos.size() == 1)
		{
			GetCombos1Rules(VectorOfStringCombos);
		}
		else if (VectorOfStringCombos.size() == 2)
		{
			GetCombos2Rules(VectorOfStringCombos);
		}
		else if (VectorOfStringCombos.size() == 3)
		{
			GetCombos3Rules(VectorOfStringCombos);
		}

	}


}

int Rule::GetValidMessagesNum(std::vector<std::string> Messages, std::map<int, Rule> RuleList)
{
	int ValidNum = 0;

	WorkOutStringCombos(RuleList);

	for (int i = 0; i < Messages.size(); i++)
	{
		for (int j = 0; j < ComboStringList.size(); j++)
		{
			if (Messages[i] == ComboStringList[j])
			{
				std::cout<< Messages[i] << " Matches" << std::endl;
				ValidNum++;
				break;
			}
		}
	}

	return ValidNum;
}

int Rule::GetRuleNum()
{
	return RuleNumber;
}

std::vector<std::string> Rule::GetComboList()
{
	return ComboStringList;
}