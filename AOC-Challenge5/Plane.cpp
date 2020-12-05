#include "Plane.h"

void Plane::ReadInBordingLits(std::string FileName)
{
	std::ifstream BordingList("BordingList.txt");

	std::string line;
	while (std::getline(BordingList, line))
	{
		if (line.size() > 0)
		{
			BordinginfoList.push_back(line);
		}
	}
}

void Plane::GetHightestSeatID()
{
	int HighestSeatID = 0;
	std::string BSPSeatID;

	for (std::vector<std::string>::iterator it = BordinginfoList.begin(); it != BordinginfoList.end(); ++it)
	{
		int SeatID = CalculateSeatID(*it);

		if (SeatID > HighestSeatID)
		{
			HighestSeatID = SeatID;
			BSPSeatID = *it;
		}
	}

	std::cout << "The Highest SeatID for the Plane with BSPID " << BSPSeatID << " is " << HighestSeatID << std::endl;
}

int Plane::CalculateSeatID(std::string BSPKey)
{
	uint16_t LowestRow = 0, HighestRow = rows;
	uint16_t LowestCol = 0, HighestCol = columns;

	for (std::string::iterator it = BSPKey.begin(); it != BSPKey.end(); ++it)
	{
		if (*it == 'F')
		{
			HighestRow = floor((float)((LowestRow + HighestRow) / 2.0f));
		}
		else if (*it == 'B')
		{
			LowestRow = ceil((float)((LowestRow + HighestRow) / 2.0f));
		}
		else if (*it == 'R')
		{
			LowestCol = ceil((float)((LowestCol + HighestCol) / 2.0f));
		}
		else if (*it == 'L')
		{
			HighestCol = floor((float)((LowestCol + HighestCol) / 2.0f));
		}
	}

	if (HighestRow == LowestRow &&
		HighestCol == LowestCol)
	{
		int SeatID = (HighestRow * 8) + LowestCol;
		PlaneLayout[HighestRow][HighestCol] = SeatID;
		return SeatID;
	}

}

void Plane::GetFreeSeat()
{
	int MySeatID = 0;
	int16_t MyRow = -1, MyCol = -1;


	bool FoundSeat = false;
	for (int row = 1; row < rows - 1 && !FoundSeat; row++)
	{
		for (int col = 0; col < columns && !FoundSeat; col++)
		{
			if (PlaneLayout[row][col] == 0)
			{
				FoundSeat = true;

				if (PlaneLayout[row + 1][col] == 0 || PlaneLayout[row - 1][col] == 0)
				{
					FoundSeat = false;
					break;
				}
				if (col + 1 < columns && col - 1 > 0)
				{
					if (PlaneLayout[row][col + 1] == 0 || PlaneLayout[row][col - 1] == 0)
					{
						FoundSeat = false;
						break;
					}
				}
			}

			if (FoundSeat)
			{
				MySeatID = (row * 8) + col;
				MyRow = row;
				MyCol = col;
			}
		}

	}
	std::cout << "My Seat is row " << MyRow << " column " << MyCol << " with SeatID is " << MySeatID;
}