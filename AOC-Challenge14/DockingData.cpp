#include "DockingData.h"

void DockingData::GetInputFromFile(const std::string FileName)
{
    MaskList.clear();
    MemList.clear();

    std::string Line;
    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return;
    }

    MaskMemSet NewMemSet;

    while (std::getline(File, Line))
    {
        if (Line.find("mask") != std::string::npos)
        {
            if (NewMemSet.Mask != "")
            {
                MaskList.push_back(NewMemSet);
            }
            NewMemSet.MemList.clear();
            int IndexPoint = Line.find_last_of("= ");
            NewMemSet.Mask = Line.substr(IndexPoint + 1, Line.size());
        }
        else
        {
            int IndexPoint = Line.find_last_of("= ");
            int MemPosB = Line.find_last_of("[");
            int MemPosE = Line.find_last_of("]");
            NewMemSet.MemList.push_back(std::make_pair(std::stoi(Line.substr(MemPosB + 1, MemPosE)), std::stoi(Line.substr(IndexPoint + 1, Line.size()))));
        }
    }

    MaskList.push_back(NewMemSet);
}

int64_t DockingData::P1TotalSumMemory()
{
    std::string HolderString = "000000000000000000000000000000000000";
    int64_t Total = 0;

    for (int i = 0; i < MaskList.size(); i++)
    {
        for (int j = 0; j < MaskList[i].MemList.size(); j++)
        {
            HolderString = "000000000000000000000000000000000000";
            std::string ValToDecimal = DecimalToBinary(MaskList[i].MemList[j].second);
            for (int s = 0; s < MaskList[i].Mask.size(); s++)
            {
                if (MaskList[i].Mask[s] == '1')
                {
                    HolderString[s] = '1';
                }
                else if (MaskList[i].Mask[s] == 'X')
                {
                    HolderString[s] = ValToDecimal[s];
                }
            }

            MemList[MaskList[i].MemList[j].first] = BinaryToDecimal(HolderString);
        }
    }

    for (std::map<int64_t, int64_t>::iterator it = MemList.begin(); it != MemList.end(); ++it)
    {
        Total += it->second;
    }

    return Total;
}

int64_t DockingData::P2TotalSumMemory()
{
    std::string HolderString = "000000000000000000000000000000000000";
    int64_t Total = 0;

    for (int i = 0; i < MaskList.size(); i++)
    {
        CurrentMask = MaskList[i].Mask;

        for (int j = 0; j < MaskList[i].MemList.size(); j++)
        {
            HolderString = "000000000000000000000000000000000000";
            std::string ValToDecimal = DecimalToBinary(MaskList[i].MemList[j].first);
            for (int s = 0; s < MaskList[i].Mask.size(); s++)
            {
                if (CurrentMask[s] == '1')
                {
                    HolderString[s] = '1';
                }
                else if (CurrentMask[s] == '0')
                {
                   HolderString[s] = ValToDecimal[s];
                }
                else if (CurrentMask[s] == 'X')
                {
                    HolderString[s] = 'X';
                }
            }
            SortFloatingIndex(HolderString, MaskList[i].MemList[j].second, 36);

        }
    }

    for (std::map<int64_t, int64_t>::iterator it = MemList.begin(); it != MemList.end(); ++it)
    {
        Total += it->second;
    }

    return Total;
}

void DockingData::SortFloatingIndex(std::string MaskedAddress, int64_t BitPosValue, int BitIndex)
{
    if (BitIndex < 0)
    {
        MemList[BinaryToDecimal(MaskedAddress)] = BitPosValue;
        return;
    }
    if (CurrentMask[BitIndex] == 'X')
    {
        MaskedAddress[BitIndex] = '0';
        SortFloatingIndex(MaskedAddress, BitPosValue, BitIndex - 1);
        MaskedAddress[BitIndex] = '1';
        SortFloatingIndex(MaskedAddress, BitPosValue, BitIndex - 1);
    }
    else
    {
        SortFloatingIndex(MaskedAddress, BitPosValue, BitIndex - 1);
    }

}



std::string DockingData::DecimalToBinary(int64_t num)
{
    int64_t StartingNum = num;
    std::string String36Bit = "000000000000000000000000000000000000";
    for (int pos = 35; pos >= 0; --pos)
    {
        if (num % 2)
        {
            String36Bit[pos] = '1';
        }
        num /= 2;
    }

    return String36Bit;
}

int64_t DockingData::BinaryToDecimal(std::string Binary)
{
    int64_t SB = 1;

    int64_t Value = 0;

    for (int i = Binary.size() - 1; i >= 0; i--)
    {
        if (Binary[i] == '1')
        {
            Value += SB;
        }
        SB *= 2;
    }

    return Value;
}