#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Tile
{
	uint16_t TileID;
	std::vector<std::string> TileLayout;

	std::string Top, Right, Bottom, Left;

	void ConstructSides();

	void Reset();
};