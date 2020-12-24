#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "VectorStructs.h"

class PocketDimention
{
private:
	std::vector<std::vector<std::vector<bool>>> Grid3D;
	std::vector<std::vector<std::vector<uint8_t>>> Grid3DNeighbour;

	std::vector<std::vector<std::vector<std::vector<bool>>>> Grid4D;
	std::vector<std::vector<std::vector<std::vector<uint8_t>>>> Grid4DNeighbour;

	uint32_t Cycles = 6;

	int MaxWidth = 0, MaxHeight = 0, MaxDepth = 1;

	void ResizeGrids();

	void NeighbourCountChange3D(Vector3 IndexPos, bool DoIIncrease);
	void NeighbourCountChange4D(Vector4 IndexPos, bool DoIIncrease);

public:

	int GetStartingGrid(std::string FileName);

	int Get3DCyclesCubeCount();
	int Get4DCyclesCubeCount();

	void SetCycles(uint32_t NewCycles);

};