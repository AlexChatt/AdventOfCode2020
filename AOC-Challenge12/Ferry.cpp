#include "Ferry.h"


Ferry::Ferry()
{
    MyWayPoint.SetWayPoint(1, 10);
}

void Ferry::GetInstructionsList(std::string FileName)
{
    std::string Line;
    std::fstream File(FileName);

    if (!File)
    {
        std::cout << "Could not open file " << FileName;
        return;
    }

    while (std::getline(File, Line))
    {
        char InstructionLetter = Line.at(0);
        int16_t InstructionValue = std::stoi(Line.substr(1, Line.size()));

        Instruction NewInstruction(InstructionLetter, InstructionValue);

        InstructionsList.push_back(NewInstruction);
    }

}

int Ferry::GetManhattanDistanceP1()
{
    int NorthSouthValue = 0, EastWestValue = 0;
    int16_t ShipDegrees = 90;

    for (std::vector<Instruction>::iterator it = InstructionsList.begin(); it != InstructionsList.end(); ++it)
    {
        switch (it->InstructionType)
        {
        case 'N':
            NorthSouthValue += it->Value;
            break;
        case 'E':
            EastWestValue += it->Value;
            break;
        case 'S':
            NorthSouthValue -= it->Value;
            break;
        case 'W':
            EastWestValue -= it->Value;
            break;
        case 'F':
            switch (ShipDegrees)
            {
            case 0:
                NorthSouthValue += it->Value;
                break;
            case 90:
                EastWestValue += it->Value;
                break;
            case 180:
                NorthSouthValue -= it->Value;
                break;
            case 270:
                EastWestValue -= it->Value;
                break;
            }
            break;
        case 'L':
            ShipDegrees = DegreesCorrection(ShipDegrees, -it->Value);
            break;
        case 'R':
            ShipDegrees = DegreesCorrection(ShipDegrees, it->Value);
            break;
        }
    }


    return std::abs(NorthSouthValue) + std::abs(EastWestValue);
}

uint16_t Ferry::DegreesCorrection(int16_t CurrentDegrees, int16_t ValueChange)
{
    int16_t NewDegrees = CurrentDegrees;

    NewDegrees += ValueChange;
    if (NewDegrees >= 360)
    {
        NewDegrees = NewDegrees - 360;
    }
    else if (NewDegrees < -0)
    {
        NewDegrees = 360 + NewDegrees;
    }

    return NewDegrees;
}


int Ferry::GetManhattanDistanceP2()
{
    int NorthSouthValue = 0, EastWestValue = 0;

    for (std::vector<Instruction>::iterator it = InstructionsList.begin(); it != InstructionsList.end(); ++it)
    {
        switch (it->InstructionType)
        {
        case 'N':
            MyWayPoint.NorthSouthUnits += it->Value;
            break;
        case 'E':
            MyWayPoint.EastWestUnits += it->Value;
            break;
        case 'S':
            MyWayPoint.NorthSouthUnits -= it->Value;
            break;
        case 'W':
            MyWayPoint.EastWestUnits -= it->Value;
            break;
        case 'F':
            NorthSouthValue += (MyWayPoint.NorthSouthUnits * it->Value);
            EastWestValue += (MyWayPoint.EastWestUnits * it->Value);
            break;
        case 'L':
            MyWayPoint.RotateWayPoint(-it->Value);
            break;
        case 'R':
            MyWayPoint.RotateWayPoint(it->Value);
            break;
        }
    }


    return std::abs(NorthSouthValue) + std::abs(EastWestValue);

}