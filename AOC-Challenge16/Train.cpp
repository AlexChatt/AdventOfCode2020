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
    bool DeleteLine = false;

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
                    break;
                }
            }

            if (RuleFailed)
            {
                ErrorRate += NearbyTicketNumbers[i][j];
                DeleteLine = true;
            }
        }

        if (DeleteLine)
        {
            DeleteLine = false;
            NearbyTicketNumbers.erase(NearbyTicketNumbers.begin() + i);
            i--;
        }
    }
    
    return ErrorRate;
}


void Train::GetCorrectIndexPerRule()
{
    bool RuleMatch = true;
    uint16_t Index = 0;

    for (int r = 0; r < RuleList.size(); r++)
    {
        while (Index < NearbyTicketNumbers[0].size())
        {
            for (int i = 0; i < NearbyTicketNumbers.size(); i++)
            {
                if (!RuleList[r].DoesNumberFitInRule(NearbyTicketNumbers[i][Index]))
                {
                    RuleMatch = false;
                    break;
                }
            }

            if (RuleMatch == true)
            {
                RuleList[r].AddPossibleTicketIndex(Index);
            }

            Index++;
            RuleMatch = true;
        }

        Index = 0;
    }
    SetLockedIndex();
}

void Train::SetLockedIndex()
{
    int TakenIndex;
    bool FoundAll = false;

    while (!FoundAll)
    {
        for (int r = 0; r < RuleList.size(); r++)
        {
            if (RuleList[r].GetRuleTicketIndex() != -1)
            {
                continue;
            }

            std::vector<int> possibleIndexes = RuleList[r].GetPossibleIndex();
            if (possibleIndexes.size() == 1)
            {
                TakenIndex = possibleIndexes[0];
                RuleList[r].SetRuleIndexForTicket(TakenIndex);
                for (int r2 = 0; r2 < RuleList.size(); r2++)
                {
                    RuleList[r2].RemovePossibleIndex(TakenIndex);
                }
                break;
            }
        }

        FoundAll = true;
        for (int r = 0; r < RuleList.size(); r++)
        {
            if (RuleList[r].GetRuleTicketIndex() == -1)
            {
                FoundAll = false;
                break;
            }
        }
    }

}

uint64_t Train::GetDepartureTotal()
{
    uint64_t DepartureTotal = 1;
    
    for (int i = 0; i < RuleList.size(); i++)
    {
        if (RuleList[i].GetName().find("departure") != std::string::npos)
        {
            DepartureTotal *= MyTicketNumbers[RuleList[i].GetRuleTicketIndex()];
        }
    }

    return DepartureTotal;
}