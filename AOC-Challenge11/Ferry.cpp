#include "Ferry.h"

Ferry::Ferry()
{
	for (int i = 1, j = -1; i <= 1 && j >= -1; i++, j--)
	{
		P1AdjacentPairs.push_back(std::make_pair(i, 0));
		P1AdjacentPairs.push_back(std::make_pair(j, 0));

		P1AdjacentPairs.push_back(std::make_pair(0, i));
		P1AdjacentPairs.push_back(std::make_pair(0, j));

		P1AdjacentPairs.push_back(std::make_pair(i, i));
		P1AdjacentPairs.push_back(std::make_pair(j, j));

		P1AdjacentPairs.push_back(std::make_pair(i, j));
		P1AdjacentPairs.push_back(std::make_pair(j, i));
	}

	for (int i = 1, j = -1; i <= 8 && j >= -8; i++, j--)
	{
		P2AdjacentPairs.push_back(std::make_pair(i, 0));
		P2AdjacentPairs.push_back(std::make_pair(j, 0));

		P2AdjacentPairs.push_back(std::make_pair(0, i));
		P2AdjacentPairs.push_back(std::make_pair(0, j));

		P2AdjacentPairs.push_back(std::make_pair(i, i));
		P2AdjacentPairs.push_back(std::make_pair(j, j));

		P2AdjacentPairs.push_back(std::make_pair(i, j));
		P2AdjacentPairs.push_back(std::make_pair(j, i));
	}


}

void Ferry::SetSeatingGrid(std::vector<std::vector<char>> SeatGrid)
{
	Grid = SeatGrid;
}

uint16_t Ferry::GetOccupiedSeatsP1()
{
	uint16_t OccupiedSeats = 0;
	uint16_t OccSeatTol = 4;
	bool HasAnythingChanged = false;
	std::vector<std::vector<char>> GridChanges = Grid;

	do
	{
		HasAnythingChanged = false;

		for (int i = 0; i < Grid.size(); i++)
		{
			for (int j = 0; j < Grid[i].size(); j++)
			{
				if (Grid[i][j] == 'L')
				{
					if (GetAdjacentOfTypeP1(1, IndexPair(i,j)) == 0)
					{
						GridChanges[i][j] = '#';
						HasAnythingChanged = true;
					}
				}
				else if (Grid[i][j] == '#')
				{
					if (GetAdjacentOfTypeP1(OccSeatTol, IndexPair(i, j)) >= OccSeatTol)
					{
						GridChanges[i][j] = 'L';
						HasAnythingChanged = true;
					}
				}
			}
		}
		Grid = GridChanges;
	} 
	while (HasAnythingChanged);

	for (int i = 0; i < Grid.size(); i++)
	{
		for (int j = 0; j < Grid[i].size(); j++)
		{
			if (Grid[i][j] == '#')
			{
				OccupiedSeats++;
			}
		}
	}

	return OccupiedSeats;
}

uint16_t Ferry::GetOccupiedSeatsP2()
{
	uint16_t OccupiedSeats = 0;
	uint16_t OccSeatTol = 5;
	bool HasAnythingChanged = false;
	std::vector<std::vector<char>> GridChanges = Grid;

	do
	{
		HasAnythingChanged = false;

		for (int i = 0; i < Grid.size(); i++)
		{
			for (int j = 0; j < Grid[i].size(); j++)
			{
				if (Grid[i][j] == 'L')
				{
					if (GetAdjacentOfTypeP2(IndexPair(i, j)) == 0)
					{
						GridChanges[i][j] = '#';
						HasAnythingChanged = true;
					}
				}
				else if (Grid[i][j] == '#')
				{
					if (GetAdjacentOfTypeP2(IndexPair(i, j)) >= OccSeatTol)
					{
						GridChanges[i][j] = 'L';
						HasAnythingChanged = true;
					}
				}
			}
		}
		Grid = GridChanges;

	} while (HasAnythingChanged);

	for (int i = 0; i < Grid.size(); i++)
	{
		for (int j = 0; j < Grid[i].size(); j++)
		{
			if (Grid[i][j] == '#')
			{
				OccupiedSeats++;
			}
		}
	}

	return OccupiedSeats;
}

int Ferry::GetAdjacentOfTypeP1(uint16_t CutOff, IndexPair IndexSet)
{
	int Matches = 0;

	for (int i = 0; i < P1AdjacentPairs.size(); i++)
	{
		IndexPair Npair(IndexSet.X + P2AdjacentPairs[i].first, IndexSet.Y + P2AdjacentPairs[i].second);

		if (!OutOfBounds(Npair))
		{
			if (Grid[Npair.X][Npair.Y] == '#')
			{
				Matches++;
				if (Matches > CutOff) { break;}
			}
		}
	}
	return Matches;
}

int Ferry::GetAdjacentOfTypeP2(IndexPair IndexSet)
{
	int Matches = 0;

	if (IsSeatInPattern(IndexSet, IndexPair(1, 0))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(-1, 0))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(0, 1))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(0, -1))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(1, 1))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(-1, -1))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(1, -1))) { Matches++; }
	if (IsSeatInPattern(IndexSet, IndexPair(-1, 1))) { Matches++; }

	return Matches;
}

bool Ferry::IsSeatInPattern(IndexPair Index, IndexPair Pattern)
{
	int XPIndex = Index.X;
	int YPIndex = Index.Y;

	while (!OutOfBounds(IndexPair(XPIndex, YPIndex)))
	{
		XPIndex += Pattern.X;
		YPIndex += Pattern.Y;
		if (!OutOfBounds(IndexPair(XPIndex, YPIndex)))
		{
			if (Grid[XPIndex][YPIndex] == '#')
			{
				return true;
			}
			else if (Grid[XPIndex][YPIndex] == 'L')
			{
				return false;
			}
		}

	}

	return false;
}

bool Ferry::OutOfBounds(IndexPair IndexSet)
{
	if (IndexSet.X < 0 || IndexSet.Y < 0)
	{
		return true;
	}
	if (IndexSet.X >= Grid.size() || IndexSet.Y >= Grid[IndexSet.X].size())
	{
		return true;
	}

	return false;
}

void Ferry::DrawGrid()
{
	for (int i = 0; i < Grid.size(); i++)
	{
		for (int j = 0; j < Grid[i].size(); j++)
		{
			std::cout << Grid[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}