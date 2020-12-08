// AOC-Challenge8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <algorithm>

#include "operations.h"

std::vector<std::string> GetLinesFromFile(std::string FileName);
std::vector<operation> GetLinesFromFile(std::vector<std::string> OperationsListText);

int32_t GetFirstCountAccumulator(std::vector<operation> OperationsListText);

int main()
{
    std::vector<std::string> FileLines = GetLinesFromFile("input.txt");
    std::vector<operation> OperationsList = GetLinesFromFile(FileLines);

    int32_t P1Accumulator = GetFirstCountAccumulator(OperationsList);
    std::cout << "The Accumulator is at count " << P1Accumulator;

    return 0;
}

std::vector<std::string> GetLinesFromFile(std::string FileName)
{
    std::vector<std::string> Lines;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return Lines;
    }

    while (std::getline(File, Line))
    {
        if (Line.size() < 0)
        {
            Lines.push_back("");
        }

        Lines.push_back(Line);
    }

    return Lines;
}

std::vector<operation> GetLinesFromFile(std::vector<std::string> OperationsListText)
{
    std::vector<operation> OpList;

    for (std::vector<std::string>::iterator Oit = OperationsListText.begin(); Oit != OperationsListText.end(); ++Oit)
    {
        operation NewOp;
        int16_t Numvalue = 0;

        if (Oit->find("nop") != std::string::npos)
        {
            NewOp.op = OpType::nop;
            NewOp.Number = Numvalue;
        }
        else if (Oit->find("acc") != std::string::npos)
        {
            NewOp.op = OpType::acc;
            std::size_t sym = Oit->find("-");
            if (sym != std::string::npos)
            {
                Numvalue = std::stoi(Oit->substr(sym, Oit->size()));
                NewOp.Number = Numvalue;
            }
            sym = Oit->find("+");
            if (sym != std::string::npos)
            {
                Numvalue = std::stoi(Oit->substr(sym, Oit->size()));
                NewOp.Number = Numvalue;
            }
        }
        else if (Oit->find("jmp") != std::string::npos)
        {
            NewOp.op = OpType::jmp;
            std::size_t sym = Oit->find("-");
            if (sym != std::string::npos)
            {
                Numvalue = std::stoi(Oit->substr(sym, Oit->size()));
                NewOp.Number = Numvalue;
            }
            sym = Oit->find("+");
            if (sym != std::string::npos)
            {
                Numvalue = std::stoi(Oit->substr(sym, Oit->size()));
                NewOp.Number = Numvalue;
            }
        }

        OpList.push_back(NewOp);
    }

    return OpList;
}

int32_t GetFirstCountAccumulator(std::vector<operation> OperationsListText)
{
    int32_t accumulator = 0;

    for (int i = 0; i < OperationsListText.size();)
    {
        if (OperationsListText[i].visited == true)
        {
            break;
        }
        OperationsListText[i].visited = true;

        if (OperationsListText[i].op == OpType::acc)
        {
            accumulator += OperationsListText[i].Number;
            i++;
        }
        else if (OperationsListText[i].op == OpType::jmp)
        {
            i += OperationsListText[i].Number;
        }
        else if (OperationsListText[i].op == OpType::nop)
        {
            i++;
        }
    }

    return accumulator;
}