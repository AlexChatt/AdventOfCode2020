#include "GameManager.h"


std::vector<uint16_t> GameManager::GetCupListAfterXRounds(int rounds)
{
	std::vector<uint16_t> FinalCupOrder;
	std::vector<uint16_t> CupsToMoved;
	std::vector<uint16_t> CupsToMoveIndexes;

	for (int i = 0; i < rounds; i++)
	{
		CupsToMoved = GetNext3Cups(CupsToMoveIndexes);
		uint16_t DestinationIndex = FindIndexOfNextDestination(Cups[CurrentCupIndex], CupsToMoved);
		uint16_t DestinationNum = Cups[DestinationIndex];

		int IndexOffset = 0;

		for (int Cindex = 0; Cindex < CupsToMoveIndexes.size(); Cindex++)
		{
			if (CupsToMoveIndexes[Cindex] == 0) { IndexOffset = 0; }

			Cups.erase(Cups.begin() + (CupsToMoveIndexes[Cindex] + IndexOffset));

			if (CupsToMoveIndexes[Cindex] + IndexOffset < CurrentCupIndex)
			{
				CurrentCupIndex--;
			}

			IndexOffset--;
		}

		DestinationIndex = GetIndexOfNum(DestinationNum);
		Cups.insert(Cups.begin() + DestinationIndex + 1, CupsToMoved.begin(), CupsToMoved.end());

		if (DestinationIndex < CurrentCupIndex) { CurrentCupIndex += 3; }

		CurrentCupIndex++;
		if(CurrentCupIndex >= Cups.size())	
		{
			CurrentCupIndex = CurrentCupIndex - Cups.size();
		}
	}

	uint16_t IndexOf1 = GetIndexOfNum(1);

	for (int i = IndexOf1 + 1; i < Cups.size(); i++)
	{
		FinalCupOrder.push_back(Cups[i]);
	}
	for (int i = 0; i < IndexOf1; i++)
	{
		FinalCupOrder.push_back(Cups[i]);
	}

	return FinalCupOrder;
}

uint16_t GameManager::GetIndexOfNum(uint16_t num)
{
	std::vector<uint16_t>::iterator it = std::find(Cups.begin(), Cups.end(), num);

	if (it != Cups.end())
	{
		return it - Cups.begin();
	}

	return -1;
}

uint16_t GameManager::FindIndexOfNextDestination(uint16_t CurrentCupNum, std::vector<uint16_t> LastCupsMoved)
{
	bool Match = false;

	while (!Match)
	{
		CurrentCupNum--;

		if (CurrentCupNum <= 0)
		{
			CurrentCupNum = 9;
		}

		for (int i = 0; i < Cups.size(); i++)
		{
			if (CurrentCupNum == Cups[i] && 
				std::find(LastCupsMoved.begin(), LastCupsMoved.end(), CurrentCupNum) == LastCupsMoved.end())
			{
				return i;
			}
		}

	}
}

std::vector<uint16_t> GameManager::GetNext3Cups(std::vector<uint16_t>& Indexes)
{
	std::vector<uint16_t> CupsToMoved;
	Indexes.clear();

	uint8_t CupIndexStart = CurrentCupIndex + 1;

	for (int i = CupIndexStart; i < CupIndexStart + 3; i++)
	{
		int tempindex = i;
		if (tempindex >= Cups.size())
		{
			tempindex = tempindex - Cups.size();
		}
		CupsToMoved.push_back(Cups[tempindex]);
		Indexes.push_back(tempindex);
	}

	return CupsToMoved;
}