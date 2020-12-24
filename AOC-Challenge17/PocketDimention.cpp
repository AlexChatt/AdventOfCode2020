#include "PocketDimention.h"

int PocketDimention::GetStartingGrid(const std::string FileName)
{
	Grid3D.clear();
	Grid4D.clear();
	Grid3DNeighbour.clear();
	Grid4DNeighbour.clear();

	std::ifstream File(FileName);
	if (!File)
	{
		std::cout << "Could not find file " << FileName << std::endl;
		return -1;
	}

	int StartHeight = 0, StartWidth = 0;

	std::string templine;
	while (std::getline(File, templine))
	{
		StartHeight++;
		StartWidth = (int)templine.size();
	}

	MaxWidth = StartWidth + 2 * Cycles + 2;
	MaxHeight = StartHeight + 2 * Cycles + 2;
	MaxDepth += 2 * Cycles + 2;

	ResizeGrids();
	int offset = Cycles + 1;

	File.clear();
	File.seekg(0);
	for (int h = 0; h < StartHeight; h++)
	{
		std::getline(File, templine);
		for (int w = 0; w < StartHeight; w++)
		{
			if (templine[w] == '#')
			{
				Grid3D[w + offset][h + offset][offset] = true;
				Grid4D[w + offset][h + offset][offset][offset] = true;
			}
		}
	}


	return 0;
}


void PocketDimention::ResizeGrids()
{
	Grid3D.resize(MaxWidth);
	Grid4D.resize(MaxWidth);

	Grid3DNeighbour.resize(MaxWidth);
	Grid4DNeighbour.resize(MaxWidth);

	for (int i = 0; i < Grid3D.size(); i++)
	{
		Grid3D[i].resize(MaxHeight);
		Grid3DNeighbour[i].resize(MaxHeight);

		Grid4D[i].resize(MaxHeight);
		Grid4DNeighbour[i].resize(MaxHeight);
	}
	for (int i = 0; i < Grid3D.size(); i++)
	{
		for (int j = 0; j < Grid3D[i].size(); j++)
		{
			Grid3D[i][j].resize(MaxDepth, false);
			Grid3DNeighbour[i][j].resize(MaxDepth, 0);

			Grid4D[i][j].resize(MaxDepth);
			Grid4DNeighbour[i][j].resize(MaxDepth);
		}
	}

	for (int i = 0; i < Grid3D.size(); i++)
	{
		for (int j = 0; j < Grid3D[i].size(); j++)
		{
			for (int k = 0; k < Grid3D[i][j].size(); k++)
			{
				Grid4D[i][j][k].resize(MaxDepth, false);
				Grid4DNeighbour[i][j][k].resize(MaxDepth, 0);
			}
		}
	}

}

int PocketDimention::Get3DCyclesCubeCount()
{
	int CubeCount = 0;

	for (int x = 0; x < MaxWidth; x++) 
	{
		for (int y = 0; y < MaxHeight; y++)
		{
			for (int z = 0; z < MaxDepth; z++) 
			{
				if (Grid3D[x][y][z]) 
				{
					NeighbourCountChange3D(Vector3(x,y,z), true);
				}
			}
		}
	}
	std::vector<std::vector<std::vector<uint8_t>>> TempGrid3DNeighbour = Grid3DNeighbour;

	for (int Cycle = 0; Cycle < Cycles; Cycle++)
	{
		for (int x = 0; x < MaxWidth; x++) 
		{
			for (int y = 0; y < MaxHeight; y++) 
			{
				for (int z = 0; z < MaxDepth; z++) 
				{
					int NeiCount = TempGrid3DNeighbour[x][y][z];

					if (!Grid3D[x][y][z] && NeiCount == 3)
					{
						Grid3D[x][y][z] = true;
						NeighbourCountChange3D(Vector3(x, y, z), true);
					}
					else if (Grid3D[x][y][z] && !(NeiCount == 2 || NeiCount == 3))
					{
						Grid3D[x][y][z] = false;
						NeighbourCountChange3D(Vector3(x, y, z), false);
					}
				}
			}
		}

		TempGrid3DNeighbour = Grid3DNeighbour;
	}

	for (int x = 0; x < MaxWidth; x++)
	{
		for (int y = 0; y < MaxHeight; y++)
		{
			for (int z = 0; z < MaxDepth; z++)
			{
				if (Grid3D[x][y][z])
				{
					CubeCount++;
				}
			}
		}
	}

	return CubeCount;
}

void PocketDimention::NeighbourCountChange3D(Vector3 IndexPos, bool DoIIncrease)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if (!(i == 0 && j == 0 && k == 0))
				{
					if (DoIIncrease)
					{
						Grid3DNeighbour[IndexPos.X + i][IndexPos.Y + j][IndexPos.Z + k] += 1;
					}
					else
					{
						Grid3DNeighbour[IndexPos.X + i][IndexPos.Y + j][IndexPos.Z + k] -= 1;
					}
				}
			}
		}
	}
}

int PocketDimention::Get4DCyclesCubeCount()
{
	int CubeCount = 0;

	for (int x = 0; x < MaxWidth; x++)
	{
		for (int y = 0; y < MaxHeight; y++)
		{
			for (int z = 0; z < MaxDepth; z++)
			{
				for (int w = 0; w < MaxDepth; w++)
				{
					if (Grid4D[x][y][z][w])
					{
						NeighbourCountChange4D(Vector4(x, y, z, w), true);
					}
				}
			}
		}
	}
	std::vector<std::vector<std::vector<std::vector<uint8_t>>>> TempGrid4DNeighbour = Grid4DNeighbour;

	for (int Cycle = 0; Cycle < Cycles; Cycle++)
	{
		for (int x = 0; x < MaxWidth; x++)
		{
			for (int y = 0; y < MaxHeight; y++)
			{
				for (int z = 0; z < MaxDepth; z++)
				{
					for (int w = 0; w < MaxDepth; w++)
					{
						int NeiCount = TempGrid4DNeighbour[x][y][z][w];

						if (!Grid4D[x][y][z][w] && NeiCount == 3)
						{
							Grid4D[x][y][z][w] = true;
							NeighbourCountChange4D(Vector4(x, y, z, w), true);
						}
						else if (Grid4D[x][y][z][w] && !(NeiCount == 2 || NeiCount == 3))
						{
							Grid4D[x][y][z][w] = false;
							NeighbourCountChange4D(Vector4(x, y, z, w), false);
						}
					}
				}
			}
		}

		TempGrid4DNeighbour = Grid4DNeighbour;
	}

	for (int x = 0; x < MaxWidth; x++)
	{
		for (int y = 0; y < MaxHeight; y++)
		{
			for (int z = 0; z < MaxDepth; z++)
			{
				for (int w = 0; w < MaxDepth; w++)
				{
					if (Grid4D[x][y][z][w])
					{
						CubeCount++;
					}
				}
			}
		}
	}

	return CubeCount;
}

void PocketDimention::NeighbourCountChange4D(Vector4 IndexPos, bool DoIIncrease)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				for (int w = -1; w <= 1; w++)
				{
					if (!(i == 0 && j == 0 && k == 0 && w == 0))
					{
						if (DoIIncrease)
						{
							Grid4DNeighbour[IndexPos.X + i][IndexPos.Y + j][IndexPos.Z + k][IndexPos.W + w] += 1;
						}
						else
						{
							Grid4DNeighbour[IndexPos.X + i][IndexPos.Y + j][IndexPos.Z + k][IndexPos.W + w] -= 1;
						}
					}
				}
			}
		}
	}
}


void PocketDimention::SetCycles(uint32_t NewCycles)
{
	Cycles = NewCycles;
}