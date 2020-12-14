// AOC-Challenge14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>

#include "MaskMemSet.h"

std::vector<MaskMemSet> GetInputFromFile(const std::string FileName);

int64_t TotalSumMemory(std::vector<MaskMemSet> MaskMemSet);
std::string DecimalToBinary(int64_t num);
int64_t BinaryToDecimal(std::string Binary);

int main()
{
    std::vector<MaskMemSet> MaskList = GetInputFromFile("input.txt");

    int64_t TotalSum = TotalSumMemory(MaskList);
    std::cout << "P1 = " << TotalSum << std::endl;

    return 0;
}

int64_t TotalSumMemory(std::vector<MaskMemSet> MaskMemSet)
{
    std::string HolderString = "000000000000000000000000000000000000";
    int64_t Total = 0;

    std::map<int64_t, int64_t> MemList;

    for (int i = 0; i < MaskMemSet.size(); i++)
    {
        for (int j = 0; j < MaskMemSet[i].MemList.size(); j++)
        {
            HolderString = "000000000000000000000000000000000000";
            std::string ValToDecimal = DecimalToBinary(MaskMemSet[i].MemList[j].second);
            for (int s = 0; s < MaskMemSet[i].Mask.size(); s++)
            {
                if (MaskMemSet[i].Mask[s] == '1') 
                {
                    HolderString[s] = '1';
                }
                else if (MaskMemSet[i].Mask[s] == '0')
                {
                    HolderString[s] = '0';
                }
                else if (MaskMemSet[i].Mask[s] == 'X')
                {
                    HolderString[s] = ValToDecimal[s];
                }
            }

            MemList[MaskMemSet[i].MemList[j].first] = BinaryToDecimal(HolderString);
        }
    }

    for (std::map<int64_t, int64_t>::iterator it = MemList.begin(); it != MemList.end(); ++it)
    {
        Total += it->second;
    }

    return Total;
}

std::string DecimalToBinary(int64_t num)
{
    int64_t StartingNum = num;
    std::string String36Bit = "000000000000000000000000000000000000";
    for (int pos = 35; pos >= 0; --pos)
    {
        if (num % 2)
        {
            String36Bit[pos] = '1';
        }
        num /= 2;
    }

    return String36Bit;
}

int64_t BinaryToDecimal(std::string Binary)
{
    int64_t SB = 1;

    int64_t Value = 0;

    for (int i = Binary.size() - 1; i > 0; i--)
    {
        if (Binary[i] == '1')
        {
            Value += SB;
        }
        SB *= 2;
    }

    return Value;
}

std::vector<MaskMemSet> GetInputFromFile(const std::string FileName)
{
    std::vector<MaskMemSet> MaskMemList;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return MaskMemList;
    }

    MaskMemSet NewMemSet;

    while (std::getline(File, Line))
    {
        if(Line.find("mask") != std::string::npos)
        {
            if (NewMemSet.Mask != "")
            {
                MaskMemList.push_back(NewMemSet);
            }
            NewMemSet.MemList.clear();
            int IndexPoint = Line.find_last_of("= ");
            NewMemSet.Mask = Line.substr(IndexPoint + 1, Line.size());
        }
        else
        {
            int IndexPoint = Line.find_last_of("= ");
            int MemPosB = Line.find_last_of("[");
            int MemPosE = Line.find_last_of("]");
            NewMemSet.MemList.push_back(std::make_pair(std::stoi(Line.substr(MemPosB+1, MemPosE)),std::stoi(Line.substr(IndexPoint + 1, Line.size()))));
        }
    }

    MaskMemList.push_back(NewMemSet);

    return MaskMemList;
}