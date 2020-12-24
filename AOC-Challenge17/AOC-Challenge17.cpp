// AOC-Challenge17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PocketDimention.h"

int main()
{
    PocketDimention MyPocketDimention;

    if (MyPocketDimention.GetStartingGrid("input.txt") == -1)
    {
        return -1;
    }
    std::cout<< "P1: Total number of cubes after 6 cycles is " << MyPocketDimention.Get3DCyclesCubeCount() << std::endl;

    std::cout << "P2: Total number of cubes after 6 cycles is " << MyPocketDimention.Get4DCyclesCubeCount() << std::endl;

    return 0;
}
