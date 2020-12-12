#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Instructions.h"
#include "WayPoint.h"

class Ferry
{
private:
	std::vector<Instruction> InstructionsList;

	uint16_t DegreesCorrection(int16_t CurrentDegrees, int16_t ValueChange);

	WayPoint MyWayPoint;

public:

	Ferry();

	void GetInstructionsList(std::string FileName);
	
	int GetManhattanDistanceP1();

	int GetManhattanDistanceP2();

};