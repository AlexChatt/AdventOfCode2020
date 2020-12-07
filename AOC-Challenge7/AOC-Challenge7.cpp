// AOC-Challenge7.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <algorithm>

#include "Bag.h"

std::vector<std::string> GetLinesFromFile(std::string FileName);

uint32_t GoldBagHolderCount(std::vector<std::string> BagTypes);

std::vector<Bag> GetAllBagRules(std::vector<std::string> bags);
std::pair<std::string, uint16_t> GetSubBagInfo(std::string SubBagRule);
uint32_t NumBagGoldHoldsCount(std::string BaseBag, std::vector<Bag> BagRules);

int main()
{
    std::vector<std::string> FileLines = GetLinesFromFile("input.txt");

    uint32_t GBCount = GoldBagHolderCount(FileLines);
    std::cout << "Total number of bags that can contain Gold Bags is " << GBCount << std::endl;

    std::vector<Bag> BagRules = GetAllBagRules(FileLines);

    uint32_t GoldBagContainsCount = NumBagGoldHoldsCount("shiny gold", BagRules);
    std::cout << "Total number of bags contained in a Gold Bags is " << GoldBagContainsCount << std::endl;

    return -1;
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

uint32_t GoldBagHolderCount(std::vector<std::string> BagTypes)
{
    std::vector<std::string> SearchText = { "shiny gold" };
    uint32_t ContainerCount = 0;

    for (int i = 0; i < SearchText.size(); i++)
    {
        for (int j = 0; j < BagTypes.size(); j++)
        {
            std::size_t LineIndex = BagTypes[j].find(SearchText[i]);
            if (LineIndex != std::string::npos)
            {
                std::size_t MatchIndex = BagTypes[j].find("contain");
                if (MatchIndex < LineIndex)
                {
                    ContainerCount++;
                    std::size_t GrabBadType = BagTypes[j].find("bags") - 1;
                    SearchText.push_back(BagTypes[j].substr(0, GrabBadType));
                    BagTypes.erase(BagTypes.begin() + j);
                    j--;
                }
            }
        }

        SearchText.erase(SearchText.begin() + i);
        i--;
    }

    return ContainerCount;
}


std::vector<Bag> GetAllBagRules(std::vector<std::string> bags)
{
    std::vector<Bag> BagRules;

    for (std::vector<std::string>::iterator it = bags.begin(); it != bags.end(); ++it)
    {
        Bag NewBag;
        std::size_t GrabBadType = it->find("bags") - 1;
        NewBag.BagName = it->substr(0, GrabBadType);

        if (it->find("no other") == std::string::npos)
        {
            if (it->find(",") != std::string::npos)
            {
                std::string Line = *it;
                std::size_t SplitLocation = it->find(",");
                std::vector<std::string> SubBagRules;
                while (SplitLocation != std::string::npos)
                {
                   SubBagRules.push_back(Line.substr(0, SplitLocation));
                   Line.erase(0, SplitLocation + 1);
                   SplitLocation = Line.find(",");
                   if (SplitLocation == std::string::npos && Line.length() > 0)
                   {
                       SplitLocation = Line.length();
                   }
                }

                for (std::vector<std::string>::iterator SubBagit = SubBagRules.begin(); SubBagit != SubBagRules.end(); ++SubBagit)
                {
                    NewBag.ContainedBags.push_back(GetSubBagInfo(*SubBagit));
                }
            }
            else
            {
                NewBag.ContainedBags.push_back(GetSubBagInfo(*it));
            }
        }

        BagRules.push_back(NewBag);
    }

   return BagRules;
}

std::pair<std::string, uint16_t> GetSubBagInfo(std::string SubBagRule)
{
    // 100% a better way
    // why i do this
    char const* digits = "0123456789";

    std::size_t const SubBagNum = SubBagRule.find_first_of(digits);
    if (SubBagNum != std::string::npos)
    {
        std::size_t BagNameIndex = SubBagRule.find_first_not_of(digits, SubBagNum);
        uint16_t NewBagPairNum = std::stoi(SubBagRule.substr(SubBagNum, BagNameIndex));
        std::size_t BagNameEnd = SubBagRule.find_last_of("bag") - 3;
        BagNameIndex += 1;
        std::string InsideBagName = SubBagRule.substr(BagNameIndex, BagNameEnd - BagNameIndex);
        return std::pair<std::string, uint16_t>(InsideBagName, NewBagPairNum);
    }

    return std::pair<std::string, uint16_t>("ErrorBag",0);
}

uint32_t NumBagGoldHoldsCount(std::string BaseBag, std::vector<Bag> BagRules)
{
    uint32_t ContainerCount = 0;

    for (std::vector<Bag>::iterator Bit = BagRules.begin(); Bit != BagRules.end(); ++Bit)
    {
        if (Bit->BagName == BaseBag)
        {
            for (std::vector<std::pair<std::string, uint16_t>>::iterator pairit = Bit->ContainedBags.begin();
                pairit != Bit->ContainedBags.end(); ++pairit)
            {
                int SubBagCount = pairit->second;
                SubBagCount += pairit->second * (NumBagGoldHoldsCount(pairit->first, BagRules));
                ContainerCount += SubBagCount;
            }
        }
    }

    return ContainerCount;
}