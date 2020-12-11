// AOC-Challenge10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

std::vector<uint16_t> GetNumbersFromFile(std::string FileName);

uint32_t Part1JoltJumpMuliplication(std::vector<uint16_t> joltageRatings);
uint64_t Part2PathCount(int num, std::vector<uint16_t> joltageRatings, std::map<uint16_t, uint64_t> &ExploredPaths);

int main()
{
	std::vector<uint16_t> joltageRatings = GetNumbersFromFile("input.txt");
    joltageRatings.push_back(0);
    std::sort(joltageRatings.begin(), joltageRatings.end());
    joltageRatings.push_back(joltageRatings[joltageRatings.size() -1] + 3);

    uint32_t JumpMuliplicationP1 = Part1JoltJumpMuliplication(joltageRatings);

    std::cout << "P1: one jumps * three jumps = " << JumpMuliplicationP1 << std::endl;

    std::map<uint16_t, uint64_t> ExploredPaths;
    uint64_t TotalCombos = Part2PathCount(0, joltageRatings, ExploredPaths);

    std::cout << "Total Combos = " << TotalCombos << std::endl;

	return 0;
}

std::vector<uint16_t> GetNumbersFromFile(std::string FileName)
{
    std::vector<uint16_t> inputs;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return inputs;
    }

    while (std::getline(File, Line))
    {
        inputs.push_back(std::stoll(Line));
    }

    return inputs;

}


uint32_t Part1JoltJumpMuliplication(std::vector<uint16_t> joltageRatings)
{
    uint16_t StartingJolt = 0;
    uint16_t MaxRange = 3;
    uint16_t OneJump = 0, ThreeJump = 0;

    bool UnSolvable = false;

    for (int i = 0; i < joltageRatings.size() - 1 && !UnSolvable; )
    {
        for (int j = i + 1; j <= i + MaxRange && j < joltageRatings.size(); i++)
        {
            if (joltageRatings[i] + 3 >= joltageRatings[j])
            {
                if (joltageRatings[j] - joltageRatings[i] == 1)
                {
                    OneJump++;
                }
                else if (joltageRatings[j] - joltageRatings[i] == 3)
                {
                    ThreeJump++;
                }

                i = j;
                break;

            }
            else
            {
                UnSolvable = true;
                break;
            }
        }
    }

    return OneJump * ThreeJump;
}


uint64_t Part2PathCount(int num, std::vector<uint16_t> joltageRatings, std::map<uint16_t, uint64_t>& ExploredPaths)
{
    if (num == joltageRatings.size() - 1)
    {
        return 1;
    }
    if (ExploredPaths.count(num))
    {
        return ExploredPaths[num];
    }

    uint64_t Answer = 0;

    for (int i = num + 1; i < joltageRatings.size(); i++)
    {
        if (joltageRatings[i] - joltageRatings[num] <= 3)
        {
            Answer += Part2PathCount(i, joltageRatings, ExploredPaths);
        }
    }

    ExploredPaths[num] = Answer;

    return Answer;
}
