#pragma once

#include <iostream>

struct Instruction
{
	char InstructionType = ' ';
	int16_t Value = 0;

	Instruction(char IType, int16_t Val)
	{
		InstructionType = IType;
		Value = Val;
	}
};