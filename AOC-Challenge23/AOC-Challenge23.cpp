// AOC-Challenge23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameManager.h"

int main()
{
    GameManager CupGameManager;

    std::vector<uint16_t> CupOrder = CupGameManager.GetCupListAfterXRounds(100);

    std::cout << "P1: Cups: ";
    for (int i = 0; i < CupOrder.size(); i++)
    {
        std::cout << CupOrder[i];
    }
}
