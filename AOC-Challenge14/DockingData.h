#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include "MaskMemSet.h"

class DockingData
{
private:

	std::vector<MaskMemSet> MaskList;
	std::map<int64_t, int64_t> MemList;
	std::string CurrentMask = "";

	std::string DecimalToBinary(int64_t num);
	int64_t BinaryToDecimal(std::string Binary);

public:

	int64_t P1TotalSumMemory();

	int64_t P2TotalSumMemory();

	void GetInputFromFile(const std::string FileName);

	void SortFloatingIndex(std::string MaskedAddress, int64_t BitPosValue, int BitIndex);
};