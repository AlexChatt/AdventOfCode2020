// AOC-Challenge2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

bool CheckPasswordValidPart1(uint16_t min, uint16_t max, char CharToLookFor, std::string password);
bool CheckPasswordValidPart2(uint16_t LetterIndex1, uint16_t LetterIndex2, char CharToLookFor, std::string password);

int main()
{
	std::ifstream passwordsFile("passwords.txt");

	if (!passwordsFile)
	{
		std::cout << "Could not open passwords.txt file";
		return -1;
	}

	const std::regex PasswordSearchReg("[^0-9]*([0-9]+)-*([0-9]+) ([a-z]): ([a-z]*)");

	int NumberValidPasswordsP1 = 0;
	int NumberValidPasswordsP2 = 0;

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

					if (CheckPasswordValidPart1(MinNumExpected, MaxNumExpected, LetterExpected, Password))
					{
						NumberValidPasswordsP1++;
					}

					if (CheckPasswordValidPart2(MinNumExpected, MaxNumExpected, LetterExpected, Password))
					{
						NumberValidPasswordsP2++;
					}
				}
			}
		}
	}

	std::cout << "Number of valid passwords for part1 is: " << NumberValidPasswordsP1 << std::endl;
	std::cout << "Number of valid passwords for part2 is: " << NumberValidPasswordsP2 << std::endl;

	return 0;
}


bool CheckPasswordValidPart1(uint16_t min, uint16_t max, char CharToLookFor, std::string password)
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

bool CheckPasswordValidPart2(uint16_t LetterIndex1, uint16_t LetterIndex2, char CharToLookFor, std::string password)
{
	bool CheckOneHasLetter = false;
	bool CheckTwoHasLetter = false;

	LetterIndex1 -= 1;
	LetterIndex2 -= 1;

	if (LetterIndex1 < password.size())
	{
		if (password[LetterIndex1] == CharToLookFor)
		{
			CheckOneHasLetter = true;
		}
	}

	if (LetterIndex2 < password.size())
	{
		if (password[LetterIndex2] == CharToLookFor)
		{
			CheckTwoHasLetter = true;
		}
	}


	return (CheckOneHasLetter ^ CheckTwoHasLetter);
}