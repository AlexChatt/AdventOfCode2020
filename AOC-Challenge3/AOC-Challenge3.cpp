// AOC-Challenge3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

bool TaskOne(std::vector<std::vector<char>> CurrentMap);
bool TaskTwo(std::vector<std::vector<char>> CurrentMap);
int GetTreesHitWithPath(std::vector<std::vector<char>> CurrentMap, uint16_t acrossjump, uint16_t downjump);

int main()
{
    std::ifstream MapFile("map.txt");

    if (!MapFile)
    {
        std::cout << "Could not find map file";
        return -1;
    }

    std::vector<std::vector<char>> Map;
    std::vector<char> newline;

    std::string line;   
    while (std::getline(MapFile, line))
    {
        if (line.size() > 0)
        {
            newline.clear();

            for (std::string::iterator it = line.begin(); it != line.end(); ++it)
            {
                newline.push_back(*it);
            }
        }
        Map.push_back(newline);
    }

    if (!TaskOne(Map))
    {
        return -1;
    }

    if (!TaskTwo(Map))
    {
        return -1;
    }

}

bool TaskOne(std::vector<std::vector<char>> CurrentMap)
{
    int TreesHit = GetTreesHitWithPath(CurrentMap, 3, 1);

    if (TreesHit != -1)
    {
        std::cout << "In this map, we would hit " << TreesHit << " Trees \n";
    }
    else
    {
        std::cout << "map fail";
        return false;
    }

    return true;
}

bool TaskTwo(std::vector<std::vector<char>> CurrentMap)
{
    int TreesHit = 0;

    std::vector<std::pair<uint16_t, uint16_t>> paths = { std::make_pair(1,1),
                                                         std::make_pair(3,1), 
                                                         std::make_pair(5,1), 
                                                         std::make_pair(7,1), 
                                                         std::make_pair(1,2) };

    uint64_t TotalTreesHit = 1;

    for (std::vector<std::pair<uint16_t, uint16_t>>::iterator it = paths.begin(); it != paths.end(); ++it)
    {
        int NewTreesHit = GetTreesHitWithPath(CurrentMap, it->first, it->second);

        if (NewTreesHit == -1)
        {
            std::cout << "map fail";
            return false;
        }
        
        TotalTreesHit *= NewTreesHit;
    }


    std::cout << "For all these paths, we would hit " << TotalTreesHit << " Trees \n";

    return true;
}


int GetTreesHitWithPath(std::vector<std::vector<char>> CurrentMap, uint16_t acrossjump, uint16_t downjump)
{
    char TreeIcon = '#';
    int TressHit = 0;

    uint16_t CurrentXIndex = 0;
    uint16_t CurrentYIndex = 0;

    if (CurrentMap.empty())
    {
        return -1;
    }

    int maxtries = CurrentMap.size() * CurrentMap[0].size();
    int attempts = 0;

    while (CurrentYIndex < CurrentMap.size())
    {
        if (CurrentMap[CurrentYIndex][CurrentXIndex] == TreeIcon)
        {
            TressHit++;
        }

        CurrentXIndex += acrossjump;
        CurrentYIndex += downjump;

        if (CurrentXIndex >= CurrentMap[0].size())
        {
            int sub = CurrentXIndex - CurrentMap[0].size();
            CurrentXIndex = sub;
        }

        attempts++;

        if (attempts >= maxtries)
        {
            std::cout << "Something has gone very wrong, map layout might be invalid?" << '\n';
            return -1;
        }

    }


    return TressHit;
}