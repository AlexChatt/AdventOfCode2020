// AOC-Challenge9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<uint64_t> GetNumbersFromFile(std::string FileName);

bool CheckValidNumber(std::vector<uint64_t> numbers, uint16_t Index, int indexrange);
uint64_t GetEncryptionWeakness(std::vector<uint64_t> numbers, uint64_t InvalidNumber);

int main()
{
    std::vector<uint64_t> numbers = GetNumbersFromFile("input.txt");

    uint64_t InvalidNumber = 0;
    int indexrange = 25;

    for (int i = indexrange; i < numbers.size(); i++)
    {
        if (!CheckValidNumber(numbers, i, indexrange))
        {
            InvalidNumber = numbers[i];
            break;
        }
    }
    std::cout << "The Invalid Number is " << InvalidNumber << std::endl;

    uint64_t EncryptionWeakness = GetEncryptionWeakness(numbers, InvalidNumber);
    std::cout << "The encryption weakness Number is " << EncryptionWeakness << std::endl;
    
    return 0;
}


std::vector<uint64_t> GetNumbersFromFile(std::string FileName)
{
    std::vector<uint64_t> inputs;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return inputs;
    }

    while (std::getline(File, Line))
    {
        inputs.push_back(std::stoll(Line));
    }

    return inputs;

}

bool CheckValidNumber(std::vector<uint64_t> numbers, uint16_t Index , int indexrange)
{
    uint16_t range = Index - indexrange;

    for (int i = range; i < Index; i++)
    {
        if (numbers[i] > numbers[Index])
        {
            continue;
        }

        for (int j = i+1; j < Index ; j++)
        {
            if (numbers[j] > numbers[Index] || numbers[i] == numbers[j])
            {
                continue;
            }

            if (numbers[i] + numbers[j] == numbers[Index])
            {
                return true;
            }

        }
    }

    return false;

}

uint64_t GetEncryptionWeakness(std::vector<uint64_t> numbers, uint64_t InvalidNumber)
{
    uint64_t Current = 0;
    std::vector<uint64_t> WorkingNumbers;

    bool FoundCombo = false;

    for (int i = 0; i < numbers.size() && !FoundCombo; i++)
    {
        WorkingNumbers.clear();
        WorkingNumbers.push_back(numbers[i]);
        Current = numbers[i];

        for (int j = i+1; j < numbers.size(); j++)
        {
            Current += numbers[j];
            WorkingNumbers.push_back(numbers[j]);

            if (Current == InvalidNumber)
            {
                FoundCombo = true; 
                break;
            }
            else if (Current > InvalidNumber)
            {
                break;
            }
        }
    }

    uint64_t min = 18446744073709551615, max = 0;

    for (int i = 0; i < WorkingNumbers.size(); i++)
    {
        min = std::min(min, WorkingNumbers[i]);
        max = std::max(max, WorkingNumbers[i]);
    }

    return (min + max);

}