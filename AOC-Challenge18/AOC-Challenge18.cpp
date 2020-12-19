// AOC-Challenge18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::string> GetEquationList(std::string FileName);

uint64_t P1GetSumOfAllEquations(std::vector<std::string> EquationList);

uint64_t P2GetSumOfAllEquations(std::vector<std::string> EquationList);
std::string SolveAdditionRun(std::string Equation);

uint64_t CustomMathsSolver(std::string Equation);


int main()
{
    std::vector<std::string> EquationList = GetEquationList("input.txt");

    std::cout << "P1 Total sum of all Equations: " << P1GetSumOfAllEquations(EquationList) << std::endl;

    std::cout << "P2 Total sum of all Equations: " << P2GetSumOfAllEquations(EquationList) << std::endl;
}

std::vector<std::string> GetEquationList(const std::string FileName)
{
    std::vector<std::string> inputs;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return inputs;
    }

    while (std::getline(File, Line))
    {
        inputs.push_back(Line);
    }

    return inputs;
}


uint64_t P1GetSumOfAllEquations(std::vector<std::string> EquationList)
{
    std::string CurrentLine;
    uint64_t totalSum = 0;

    for (std::vector<std::string>::iterator it = EquationList.begin(); it != EquationList.end(); ++it)
    {
        bool BracketsDone = false;

        CurrentLine = *it;

        while (!BracketsDone)
        {
            std::size_t BracketStartIndex = CurrentLine.find_last_of('(');
            if (BracketStartIndex != std::string::npos)
            {
                std::size_t BracketEndIndex = CurrentLine.find_first_of(')', BracketStartIndex);
                std::string BracketString = CurrentLine.substr(BracketStartIndex + 1, BracketEndIndex - (BracketStartIndex + 1));
                uint64_t BracketsSum = CustomMathsSolver(BracketString);
                CurrentLine.erase(BracketStartIndex, (BracketEndIndex+1) - BracketStartIndex);
                CurrentLine.insert(BracketStartIndex, std::to_string(BracketsSum));
            }
            else
            {
                BracketsDone = true;
            }
        }

        totalSum += CustomMathsSolver(CurrentLine);
    }

    return totalSum;
}

uint64_t P2GetSumOfAllEquations(std::vector<std::string> EquationList)
{
    std::string CurrentLine;
    uint64_t totalSum = 0;

    for (std::vector<std::string>::iterator it = EquationList.begin(); it != EquationList.end(); ++it)
    {
        bool BracketsDone = false;
        CurrentLine = *it;

        while (!BracketsDone)
        {
            std::size_t BracketStartIndex = CurrentLine.find_last_of('(');
            if (BracketStartIndex != std::string::npos)
            {
                std::size_t BracketEndIndex = CurrentLine.find_first_of(')', BracketStartIndex);
                std::string BracketString = CurrentLine.substr(BracketStartIndex + 1, BracketEndIndex - (BracketStartIndex + 1));
                uint64_t BracketsSum = CustomMathsSolver(SolveAdditionRun(BracketString));
                CurrentLine.erase(BracketStartIndex, (BracketEndIndex + 1) - BracketStartIndex);
                CurrentLine.insert(BracketStartIndex, std::to_string(BracketsSum));
            }
            else
            {
                BracketsDone = true;
            }
        }

        totalSum += CustomMathsSolver(SolveAdditionRun(CurrentLine));
    }

    return totalSum;
}

std::string SolveAdditionRun(std::string Equation)
{
    std::istringstream ss(Equation);
    std::string temp;

    bool ToAdd = false;
    uint64_t FirstNum = -1;
    uint64_t NewSum;
    std::string PostAdditionEquation;

    while (std::getline(ss, temp, ' '))
    {
        if (temp[0] == '+')
        {
            ToAdd = true;
        }
        else if (temp[0] == '*')
        {
            if (FirstNum == -1)
            {
                PostAdditionEquation += " * ";
            }
            else
            {
                PostAdditionEquation += std::to_string(FirstNum) + " * ";
            }
        }
        else if (FirstNum != -1 && ToAdd)
        {
            NewSum = FirstNum + std::stoll(temp);
            PostAdditionEquation += std::to_string(NewSum);
            FirstNum = -1;
            ToAdd = false;
        }
        else
        {
            FirstNum = std::stoll(temp);
            if (ToAdd)
            {
                std::size_t LastAddedNumberIndex = PostAdditionEquation.find_last_of(std::to_string(NewSum));
                if (LastAddedNumberIndex != std::string::npos)
                {
                    std::size_t numsize = std::to_string(NewSum).size();
                    PostAdditionEquation.erase(PostAdditionEquation.size() - numsize, numsize);
                    NewSum += FirstNum;
                    PostAdditionEquation += std::to_string(NewSum);
                }
                FirstNum = -1;
                ToAdd = false;
            }
        }
    }

    if (FirstNum != -1 && !ToAdd)
    {
        PostAdditionEquation += std::to_string(FirstNum);
    }

    return PostAdditionEquation;
}

uint64_t CustomMathsSolver(std::string Equation)
{
    std::istringstream ss(Equation);
    std::string temp;

    char Operation = ' ';
    uint64_t Sum = 0;

    while (std::getline(ss, temp, ' '))
    {
        if (temp[0] == '+' || temp[0] == '*')
        {
            Operation = temp[0];
        }
        else
        {
            if (Operation == '+')
            {
                Sum += std::stoll(temp);
                Operation = ' ';
            }
            else if (Operation == '*')
            {
                Sum *= std::stoll(temp);
                Operation = ' ';
            }
            else
            {
                Sum = std::stoll(temp);
            }
        }
    }

    return Sum;
}
