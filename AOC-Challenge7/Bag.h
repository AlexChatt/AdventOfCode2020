#pragma once

#include <string>
#include <utility> 
#include <vector>

struct Bag
{
public:

	std::string BagName;
	std::vector<std::pair<std::string, uint16_t>> ContainedBags;

};