// AOC-Challenge2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

bool CheckPasswordValid(uint16_t min, uint16_t max, char CharToLookFor, std::string password);

int main()
{
	std::ifstream passwordsFile("passwords.txt");

	if (!passwordsFile)
	{
		std::cout << "Could not open passwords.txt file";
		return -1;
	}

	std::regex PasswordSearchReg("[^0-9]*([0-9]+)-*([0-9]+) ([a-z]): ([a-z]*)");

	uint16_t NumberValidPasswords = 0;

	std::string line;
	while (std::getline(passwordsFile, line))
	{
		std::string Password;
		char LetterExpected;
		int MinNumExpected;
		int MaxNumExpected;

		if (line.size() > 0)
		{
			if (std::regex_match(line, PasswordSearchReg))
			{
				for (std::smatch foundMatches; std::regex_search(line, foundMatches, PasswordSearchReg); line = foundMatches.suffix())
				{
					MinNumExpected = std::stoi(foundMatches[1]);
					MaxNumExpected = std::stoi(foundMatches[2]);
					LetterExpected = ((std::string)foundMatches[3])[0];
					Password = foundMatches[4];

					if (CheckPasswordValid(MinNumExpected, MaxNumExpected, LetterExpected, Password))
					{
						NumberValidPasswords++;
					}
				}
			}
		}
	}
	std::cout << "number of valid passwords is: " << NumberValidPasswords;

	return 0;
}


bool CheckPasswordValid(uint16_t min, uint16_t max, char CharToLookFor, std::string password)
{
	int Count = 0;

	for (std::string::iterator it = password.begin(); it != password.end(); ++it)
	{
		if (*it == CharToLookFor)
		{
			Count++;
		}
	}

	if (Count >= min && Count <= max)
	{
		return true;
	}

	return false;
}