#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

class GameManager
{
private:

	std::vector<uint16_t> Cups = { 3,1,5,6,7,9,8,2,4 };
	uint16_t CurrentCupIndex = 0;

	uint16_t GetIndexOfNum(uint16_t num);
	uint16_t FindIndexOfNextDestination(uint16_t CurrentCupNum, std::vector<uint16_t> LastCupsMoved);
	std::vector<uint16_t> GetNext3Cups(std::vector<uint16_t>& Indexes);

public:

	std::vector<uint16_t> GetCupListAfterXRounds(int rounds);

};