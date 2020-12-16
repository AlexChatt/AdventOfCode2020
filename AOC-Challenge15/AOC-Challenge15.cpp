// AOC-Challenge15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int GetPosNumber(std::vector<int> NumberList, int pos);

int main()
{
    std::vector<int> Numbers{ 10,16,6,0,1,17 };

    std::cout << "P1: 2020 element = " << GetPosNumber(Numbers, 2020) << std::endl;

    std::cout << "P2: 30000000 element = " << GetPosNumber(Numbers, 30000000) << std::endl;

    return 0;
}

int GetPosNumber(std::vector<int> NumberList, int pos)
{
    std::map<int, int> IndexList;
    int NextToPush = -1;

    for (int i = 0; i < NumberList.size() - 1; i++)
    {
        IndexList[NumberList[i]] = i + 1;
    }

    while (NumberList.size() < pos)
    {
        int LastNum = NumberList[NumberList.size() - 1];

        if (IndexList.count(LastNum))
        {
           int Holder = IndexList[LastNum];
           if (NextToPush != -1)
           {
              IndexList[NumberList[NumberList.size() - 1]] = NextToPush;
           }
           NumberList.push_back(NumberList.size() - Holder);
           NextToPush = NumberList.size();
        }
        else
        {
            if (NextToPush == -1)
            {
                IndexList[NumberList[NumberList.size() - 1]] = NumberList.size();
            }
            else
            {
                IndexList[NumberList[NumberList.size() - 1]] = NextToPush;
            }
            NumberList.push_back(0);
            NextToPush = NumberList.size();
        }

    }

    return NumberList[pos - 1];
}