#pragma once

#include <string>
#include <vector>

enum class OpType { nop, acc, jmp, none };

struct operation
{
public:

	OpType op = OpType::none;
	int16_t Number = 0;
	bool visited = false;

};