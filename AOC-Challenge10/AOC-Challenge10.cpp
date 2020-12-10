// AOC-Challenge10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<uint16_t> GetNumbersFromFile(std::string FileName);

uint16_t GetMax(std::vector<uint16_t> adapterLits);
uint32_t Part1JoltJumpMuliplication(std::vector<uint16_t> joltageRatings);

int main()
{
	std::vector<uint16_t> joltageRatings = GetNumbersFromFile("input.txt");
    joltageRatings.push_back(0);
    std::sort(joltageRatings.begin(), joltageRatings.end());

    uint32_t JumpMuliplicationP1 = Part1JoltJumpMuliplication(joltageRatings);

    std::cout << "P1: one jumps * three jumps = " << JumpMuliplicationP1 << std::endl;

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

uint16_t GetMax(std::vector<uint16_t> adapterLits)
{
    uint16_t max = 0;

    for (int i = 0; i < adapterLits.size(); i++)
    {
        max = std::max(max, adapterLits[i]);
    }

    return max + 3;
}

uint32_t Part1JoltJumpMuliplication(std::vector<uint16_t> joltageRatings)
{
    uint16_t StartingJolt = 0;
    uint16_t MaxRange = 3;
    uint16_t OneJump = 0, ThreeJump = 0;

    joltageRatings.push_back(GetMax(joltageRatings));

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

