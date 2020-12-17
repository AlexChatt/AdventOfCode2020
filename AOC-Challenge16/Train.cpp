#include "Train.h"


void Train::GetTicketandRules(const std::string FileName)
{
    std::vector<std::string> inputs;
    std::string Line;
    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
    }
    while (std::getline(File, Line))
    {
        inputs.push_back(Line);
    }

    int SpaceIndex = 0;

    for (int i = 0; i < inputs.size(); i++)
    {
        if (inputs[i] == "")
        {
            SpaceIndex = i;
            break;
        }
        std::size_t indexpos = inputs[i].find(":");
        Rule NewRule(inputs[i].substr(0, indexpos));
        indexpos += 2;

        std::size_t Rangepos = inputs[i].find("-");
        int MinOne, MaxOne;
        int MinTwo, MaxTwo;

        MinOne = std::stoi(inputs[i].substr(indexpos, Rangepos));
        indexpos = inputs[i].find("or ");
        MaxOne = std::stoi(inputs[i].substr(Rangepos + 1, indexpos -1));
        NewRule.SetFirstRange(MinOne, MaxOne);

        Rangepos = inputs[i].find_last_of("-");
        MinTwo = std::stoi(inputs[i].substr(indexpos + 3, Rangepos));
        MaxTwo = std::stoi(inputs[i].substr(Rangepos + 1, inputs[i].size()));
        NewRule.SetSecondRange(MinTwo, MaxTwo);

        RuleList.push_back(NewRule);
    }

    SpaceIndex+=2;
    std::istringstream ss(inputs[SpaceIndex]);
    std::string temp;
    while (std::getline(ss, temp, ','))
    {
        MyTicketNumbers.push_back(std::stoi(temp));
    }
    SpaceIndex+=3;

    for (int i = SpaceIndex; i < inputs.size(); i++)
    {
        std::vector<int> NewLine;
        std::istringstream newline(inputs[i]);
        while (std::getline(newline, temp, ','))
        {
            NewLine.push_back(std::stoi(temp));
        }
        NearbyTicketNumbers.push_back(NewLine);
    }
}

int Train::GetTotalErrorRate()
{
    int ErrorRate = 0;
    bool RuleFailed = true;

    for (int i = 0; i < NearbyTicketNumbers.size(); i++)
    {
        for (int j = 0; j < NearbyTicketNumbers[i].size(); j++)
        {
            RuleFailed = true;

            for (int r = 0; r < RuleList.size(); r++)
            {
                if (RuleList[r].DoesNumberFitInRule(NearbyTicketNumbers[i][j]))
                {
                    RuleFailed = false;
                }
            }

            if (RuleFailed)
            {
                ErrorRate += NearbyTicketNumbers[i][j];
                NearbyTicketNumbers[i].erase(NearbyTicketNumbers[i].begin() + j);
                j--;
            }
        }
    }
    
    return ErrorRate;
}

uint64_t Train::GetDepartureMultiTotal()
{
    uint64_t DepartureMultiTotal = 0;


    return DepartureMultiTotal;
}