// AOC-Challenge12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Ferry.h"

int main()
{
    Ferry MyFerry;
    MyFerry.GetInstructionsList("input.txt");

    int P1ManDistance = MyFerry.GetManhattanDistanceP1();

    std::cout << "P1: The Ships Manhattan distance was " << P1ManDistance << std::endl;

    int P2ManDistance = MyFerry.GetManhattanDistanceP2();

    std::cout << "P2: The Ships Manhattan distance was " << P2ManDistance << std::endl;
}
