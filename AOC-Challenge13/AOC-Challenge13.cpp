// AOC-Challenge13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

std::vector<std::string> GetInputFromFile(const std::string FileName);

uint32_t P1GetEarliestBusMult(const std::vector<std::string> BusInfo);

long long P2GetEarliestTimeStamp(const std::vector<std::string> BusInfo);
long long chineseRemainderInv(long long a, long long m);

int main()
{
    std::vector<std::string> BusInfo = GetInputFromFile("input.txt");

    uint32_t P1Answer = P1GetEarliestBusMult(BusInfo);

    std::cout << "P1: ID of earliest bus * number of minutes you'll need to wait = " << P1Answer << std::endl;

    long long P2Answer = P2GetEarliestTimeStamp(BusInfo);

    std::cout<< "P2: Earliest timestamp for all Input times: " << P2Answer << std::endl;
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

long long P2GetEarliestTimeStamp(const std::vector<std::string> BusInfo)
{
    if (BusInfo.size() < 2)
    {
        return -1;
    }

    std::istringstream ss(BusInfo[1]);
    std::string temp;
    int Total = 0, LineNum = 0;
    std::vector<int> BusIDs;
    std::vector<int> num, rem;

    while (std::getline(ss, temp, ','))
    {
        if (temp != "x")
        {
            num.push_back(std::stoi(temp));
            rem.push_back(std::stoi(temp) - LineNum);
        }
        LineNum++;
    }

    long long prod = 1;
    for (int i = 0; i < num.size(); i++)
    {
        prod *= num[i];
    }

    long long result = 0;
    for (int i = 0; i < num.size(); i++)
    {
        long long pp = prod / num[i];
        result += rem[i] * chineseRemainderInv(pp, num[i]) * pp;
    }

    return result % prod;
}


// Returns modulo inverse of a with respect to m using extended 
// Euclid Algorithm. Refer below post for details: 
// https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ 
long long chineseRemainderInv(long long a, long long m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclid Algorithm 
    while (a > 1)
    {
        // q is quotient 
        q = a / m;

        t = m;

        // m is remainder now, process 
        // same as euclid's algo 
        m = a % m; a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive 
    if (x1 < 0)
        x1 += m0;

    return x1;
}
