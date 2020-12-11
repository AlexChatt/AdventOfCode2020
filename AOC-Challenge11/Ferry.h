#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include "IndexPair.h"

class Ferry
{
private:
	std::vector<std::vector<char>> Grid;

	std::vector<std::pair <int16_t, int16_t>> P1AdjacentPairs;

	int GetAdjacentOfTypeP1(uint16_t CutOff, IndexPair IndexSet);

	int GetAdjacentOfTypeP2(IndexPair IndexSet);
	bool IsSeatInPattern(IndexPair Index, IndexPair Pattern);

	uint16_t GetOccupiedSeatsTotal();

	bool OutOfBounds(IndexPair IndexSet);
	void DrawGrid();

public:

	Ferry();

	void SetSeatingGrid(std::vector<std::vector<char>> SeatGrid);

	uint16_t GetOccupiedSeatsP1();
	uint16_t GetOccupiedSeatsP2();

};