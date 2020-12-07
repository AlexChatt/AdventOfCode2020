// AOC-Challenge4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int GetValidPassportsP1(std::vector<std::string> PassportList);
int GetValidPassportsP2(std::vector<std::string> PassportList);
bool ValidateData(std::string Data);

int main()
{
	std::ifstream passports("passport_info.txt");

	if (!passports)
	{
		std::cout<<"Cant find passport file";
		return -1;
	}

	std::string FullLineInfo = "";
	std::vector<std::string> PassportList;

	std::string line;
	while (std::getline(passports, line))
	{
		if (line.size() > 0)
		{
			if (FullLineInfo != "") { FullLineInfo += " "; }
			FullLineInfo += line;
		}
		else
		{
			PassportList.push_back(FullLineInfo);
			FullLineInfo = "";
		}
	}
	if (FullLineInfo != "")
	{
		PassportList.push_back(FullLineInfo);
	}

	const int ValidPassportsP1 = GetValidPassportsP1(PassportList);
	std::cout << "There are a total of " << ValidPassportsP1 << " Valid Passports (part 1)" << std::endl;

	const int ValidPassportsP2 = GetValidPassportsP2(PassportList);
	std::cout << "There are a total of " << ValidPassportsP2 << " Valid Passports (part 2)" << std::endl;

	return 0;
}

int GetValidPassportsP1(std::vector<std::string> PassportList)
{
	std::vector<std::string> ValidFields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	int ValidPassports = 0;

	bool valid = true;

	for (std::vector<std::string>::iterator it = PassportList.begin(); it != PassportList.end(); ++it)
	{
		valid = true;

		for (std::vector<std::string>::iterator vit = ValidFields.begin(); vit != ValidFields.end(); ++vit)
		{
			if (it->find(*vit) == std::string::npos)
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			ValidPassports++;
		}
	}

	return ValidPassports;
}

int GetValidPassportsP2(std::vector<std::string> PassportList)
{
	std::vector<std::string> ValidFields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	int ValidPassports = 0;

	bool valid = true;

	for (std::vector<std::string>::iterator it = PassportList.begin(); it != PassportList.end(); ++it)
	{
		valid = true;

		for (std::vector<std::string>::iterator vit = ValidFields.begin(); vit != ValidFields.end(); ++vit)
		{
			if (it->find(*vit) == std::string::npos)
			{
				valid = false;
				break;
			}
		}

		if (valid && ValidateData(*it))
		{
			ValidPassports++;
		}
	}

	return ValidPassports;
}


bool ValidateData(std::string Data)
{
	std::vector<std::string> Catagories;
	std::string Catagory;
	std::istringstream tokenStream(Data);
	while (std::getline(tokenStream, Catagory, ' '))
	{
		Catagories.push_back(Catagory);
	}

	for (std::vector<std::string>::iterator it = Catagories.begin(); it != Catagories.end(); ++it)
	{
		const std::size_t pos = it->find(":") + 1;
		const std::string Data = it->substr(pos);

		if (it->find("byr") != std::string::npos)
		{
			if (std::stoi(Data) < 1920 || std::stoi(Data) > 2002)
			{
				return false;
			}
		}
		else if (it->find("iyr") != std::string::npos)
		{
			if (std::stoi(Data) < 2010 || std::stoi(Data) > 2020)
			{
				return false;
			}
		}
		else if (it->find("eyr") != std::string::npos)
		{
			if (std::stoi(Data) < 2020 || std::stoi(Data) > 2030)
			{
				return false;
			}
		}
		else if (it->find("hgt") != std::string::npos)
		{
			const std::size_t cmcheck = it->find("cm");
			const std::size_t incheck = it->find("in");
			if (cmcheck != std::string::npos)
			{
				if (std::stoi(Data) < 150 || std::stoi(Data) > 193)
				{
					return false;
				}
			}
			else if(incheck != std::string::npos)
			{
				if (std::stoi(Data) < 59 || std::stoi(Data) > 76)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (it->find("hcl") != std::string::npos)
		{
			if (!std::regex_match(Data, std::regex("#[a-f,0-9]{6}")))
			{
				return false;
			}
		}
		else if (it->find("ecl") != std::string::npos)
		{
			std::vector<std::string> ValidColours = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
			bool FoundMatch = false;
			
			for (std::vector<std::string>::iterator cit = ValidColours.begin(); cit != ValidColours.end(); ++cit)
			{
				if (Data == *cit)
				{
					FoundMatch = true;
					break;
				}
			}

			if (!FoundMatch)
			{
				return false;
			}
		}
		else if (it->find("pid") != std::string::npos)
		{
			if (!std::regex_match(Data, std::regex("^[0-9]{9}$")))
			{
				return false;
			}
		}
	}

	return true;
}