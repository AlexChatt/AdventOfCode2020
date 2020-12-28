#include "TileMap.h"


bool TileMap::ConstuctTileMap(const std::string filename)
{
	std::ifstream File(filename);
	if (!File)
	{
		std::cout << "Could not find file " << filename << std::endl;
		return false;
	}

	Tile NewTile;

	std::string templine;
	while (std::getline(File, templine))
	{
		std::size_t NewTileCheck = templine.find_last_of("Tile");
		if (NewTileCheck != std::string::npos)
		{
			std::size_t EndOfNumber = templine.find(":")-1;
			NewTile.TileID = std::stoi(templine.substr(NewTileCheck + 1, EndOfNumber - NewTileCheck + 1));
		}
		else if (templine != "")
		{
			NewTile.TileLayout.push_back(templine);
		}
		else
		{
			NewTile.ConstructSides();
			MyTiles.push_back(NewTile);
			NewTile.Reset();
		}
	}

	NewTile.ConstructSides();
	MyTiles.push_back(NewTile);
	NewTile.Reset();

	return true;
}

uint64_t TileMap::GetCornersIDMulti()
{
	uint64_t CornerSum = 1;

	std::vector<uint16_t> Corners;
	GetTopRight(Corners);
	GetTopLeft(Corners);
	GetBottomRight(Corners);
	GetBottomLeft(Corners);

	for (int i = 0; i < Corners.size(); i++)
	{
		CornerSum *= Corners[i];
	}

	return CornerSum;
}

void TileMap::GetTopRight(std::vector<uint16_t> &CornersFound)
{
	bool MatchFound = false;

	for (int i = 0; i < MyTiles.size(); i++)
	{
		MatchFound = false;
		std::string CurrentTop = MyTiles[i].Top;
		std::string CurrentRight = MyTiles[i].Right;

		for (int j = 0; j < MyTiles.size(); j++)
		{
			if (i == j) { continue; }

			if (MyTiles[j].Bottom == CurrentTop || MyTiles[j].Left == CurrentRight)
			{
				MatchFound = true;
				break;
			}
		}

		if (!MatchFound)
		{
			CornersFound.push_back(MyTiles[i].TileID);
			break;
		}
	}

}

void TileMap::GetTopLeft(std::vector<uint16_t> &CornersFound)
{
	for (int i = 0; i < MyTiles.size(); i++)
	{

	}
}

void TileMap::GetBottomRight(std::vector<uint16_t> &CornersFound)
{
	for (int i = 0; i < MyTiles.size(); i++)
	{

	}
}

void TileMap::GetBottomLeft(std::vector<uint16_t> &CornersFound)
{
	for (int i = 0; i < MyTiles.size(); i++)
	{

	}
}