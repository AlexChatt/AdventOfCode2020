#pragma once

#include <string>
#include <vector>
#include <utility>

struct MaskMemSet
{
public:
	std::string Mask = "";
	std::vector<std::pair <int64_t, int64_t>> MemList;
};