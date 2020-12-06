// AOC-Challenge6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> GetLinesFromFile(std::string FileName);

uint32_t GetYesCount(std::vector<std::string> Input);
bool CheckCharNotInVector(char letter, std::vector<char> List);

uint32_t GetFullYesCount(std::vector<std::string> Input);
void CheckLetterStillValid(std::string letters, std::vector<char> &List);

int main()
{
    std::vector<std::string> FileLines = GetLinesFromFile("input.txt");

    if (FileLines.size() <= 0)
    {
        return -1;
    }

    uint32_t TotalCountP1 = GetYesCount(FileLines);
    std::cout << "Total number of questions that groups answered yes to is " << TotalCountP1 << std::endl;


    uint32_t TotalCountP2 = GetFullYesCount(FileLines);
    std::cout << "Total number of questions that everyone in the groups answered yes to is " << TotalCountP2 << std::endl;

    return 0;
}


std::vector<std::string> GetLinesFromFile(std::string FileName)
{
    std::vector<std::string> Lines;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return Lines;
    }
  
    while (std::getline(File, Line))
    {
        if (Line.size() < 0)
        {
            Lines.push_back("");
        }

        Lines.push_back(Line);
    }

    return Lines;
}


uint32_t GetYesCount(std::vector<std::string> Input)
{
    uint32_t TotalCount = 0;

    std::vector<char> LettersSeen;

    for (std::vector<std::string>::iterator it = Input.begin(); it != Input.end(); ++it)
    {
        if (*it == "")
        {
            TotalCount += LettersSeen.size();
            LettersSeen.clear();
        }
        else
        {
            std::string line = *it;
            for (std::string::iterator sit = line.begin(); sit != line.end(); ++sit)
            {
                if (CheckCharNotInVector(*sit, LettersSeen))
                {
                    LettersSeen.push_back(*sit);
                }
            }
        }
    }

    if (LettersSeen.size() > 0)
    {
        TotalCount += LettersSeen.size();
        LettersSeen.clear();
    }


    return TotalCount;
}

bool CheckCharNotInVector(char letter, std::vector<char> List)
{
    for (std::vector<char>::iterator cit = List.begin(); cit != List.end(); ++cit)
    {
        if (*cit == letter)
        {
            return false;
        }
    }

    return true;
}

uint32_t GetFullYesCount(std::vector<std::string> Input)
{
    uint32_t TotalCount = 0;
    bool NewSet = true;

    std::vector<char> LettersSeen;

    for (std::vector<std::string>::iterator it = Input.begin(); it != Input.end(); ++it)
    {
        if (*it == "")
        {
            TotalCount += LettersSeen.size();
            LettersSeen.clear();
            NewSet = true;
        }
        else
        {
            std::string line = *it;
            if (NewSet)
            {
                for (std::string::iterator sit = line.begin(); sit != line.end(); ++sit)
                {
                    if (NewSet)
                    {
                        LettersSeen.push_back(*sit);
                    }
                }
                NewSet = false;
            }
            else
            {
                CheckLetterStillValid(line, LettersSeen);
            }
        }
    }

    if (LettersSeen.size() > 0)
    {
        TotalCount += LettersSeen.size();
        LettersSeen.clear();
    }

    return TotalCount;
}

void CheckLetterStillValid(std::string letters, std::vector<char> &List)
{
    bool MatchFound = false;

    for (std::vector<char>::iterator cit = List.begin(); cit != List.end();)
    {
        for (std::string::iterator sit = letters.begin(); sit != letters.end(); ++sit)
        {
            if (*sit == *cit)
            {
                MatchFound = true;
            }
        }

        if (!MatchFound)
        {
            cit = List.erase(cit);
        }
        else
        {
            ++cit;
            MatchFound = false;
        }
    }
}