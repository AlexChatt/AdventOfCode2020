// AOC-Challenge13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

std::vector<std::string> GetInputFromFile(const std::string FileName);

uint32_t P1GetEarliestBusMult(const std::vector<std::string> BusInfo);


int main()
{
    std::vector<std::string> BusInfo = GetInputFromFile("input.txt");

    uint32_t P1Answer = P1GetEarliestBusMult(BusInfo);

    std::cout << "P1: ID of earliest bus * number of minutes you'll need to wait = " << P1Answer << std::endl;
}


std::vector<std::string> GetInputFromFile(const std::string FileName)
{
    std::vector<std::string> inputs;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return inputs;
    }

    while (std::getline(File, Line))
    {
        inputs.push_back(Line);
    }

    return inputs;
}

uint32_t P1GetEarliestBusMult(const std::vector<std::string> BusInfo)
{
    if (BusInfo.size() < 2)
    {
        return -1;
    }

    uint32_t EarlyTime = std::stoi(BusInfo[0]);

    std::vector<uint32_t> BusIDs;
    std::istringstream ss(BusInfo[1]);
    std::string temp;

    while (std::getline(ss, temp, ','))
    {
        if (temp != "x")
        {
            BusIDs.push_back(std::stoi(temp));
        }
    }

    uint32_t EarliestBusTime = -1;
    uint32_t WaitTime = 0;
    uint32_t BestBusID = 0;

    for (int i = 0; i < BusIDs.size(); i++)
    {
        float Divide = (float)EarlyTime / (float)BusIDs[i];
        uint32_t NextTime = std::ceil(Divide) * BusIDs[i];

        if (NextTime < EarliestBusTime)
        {
            EarliestBusTime = NextTime;
            BestBusID = BusIDs[i];
            WaitTime = EarliestBusTime - EarlyTime;
        }
    }

    return BestBusID * WaitTime;

}