// AOC-Challenge14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DockingData.h"

int main()
{
    DockingData DockingManager;
    DockingManager.GetInputFromFile("input.txt");
    std::cout << "P1 = " << DockingManager.P1TotalSumMemory() << std::endl;


    DockingManager.GetInputFromFile("input.txt");
    std::cout << "P2 = " << DockingManager.P2TotalSumMemory() << std::endl;

    return 0;
}
