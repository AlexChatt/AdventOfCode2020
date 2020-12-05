#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h> 
#include <fstream>

class Plane
{
private:

	std::vector<std::string> BordinginfoList;

	static const uint16_t rows = 127;
	static const uint16_t columns = 7;
	int PlaneLayout[rows][columns] = { 0 };

public:

	void ReadInBordingLits(std::string FileName);
	void GetHightestSeatID();
	int CalculateSeatID(std::string BSPKey);
	void GetFreeSeat();
};