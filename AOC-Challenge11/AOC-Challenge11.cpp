// AOC-Challenge11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <string>

#include "Ferry.h"

std::vector<std::vector<char>> GetGridFromFile(std::string FileName);

int main()
{
    Ferry MyFerry;
    MyFerry.SetSeatingGrid(GetGridFromFile("input.txt"));
    
    uint16_t OccupiedSeats = MyFerry.GetOccupiedSeatsP1();
    std::cout << "P1: Total number of occupied seats on the Ferry are " << OccupiedSeats << std::endl;
    
    MyFerry.SetSeatingGrid(GetGridFromFile("input.txt"));

    OccupiedSeats = MyFerry.GetOccupiedSeatsP2();
    std::cout << "P2: Total number of occupied seats on the Ferry are " << OccupiedSeats << std::endl;

    return 0;
}


std::vector<std::vector<char>> GetGridFromFile(std::string FileName)
{
    std::vector<std::vector<char>> grid;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return grid;
    }

    while (std::getline(File, Line))
    {
        std::vector<char> gridLine;
        for (std::string::iterator it = Line.begin(); it != Line.end(); ++it)
        {
            gridLine.push_back(*it);
        }
        grid.push_back(gridLine);
    }

    return grid;
}
