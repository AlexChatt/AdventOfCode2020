#include "MonsterMessages.h"

void MonsterManager::SetRulesAndMessages(std::string FileName)
{
    std::vector<std::string> inputs;
    std::string Line;

    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return;
    }

    while (std::getline(File, Line))
    {
        if (Line.find(":") == std::string::npos && Line != "")
        {
            Messages.push_back(Line);
        }
        else if(Line != "")
        {
            Rule NewRule;
            NewRule.SetInfo(Line);
            RuleList[NewRule.GetRuleNum()] = NewRule;
        }

    }

    return;

}


int MonsterManager::GetValidMessNumForRule(int RuleNum)
{
    int ValidNum = 0;

    ValidNum = RuleList[RuleNum].GetValidMessagesNum(Messages, RuleList);

    return ValidNum;
}