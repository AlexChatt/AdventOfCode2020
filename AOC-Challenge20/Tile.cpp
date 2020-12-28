
#include "Tile.h"


void Tile::ConstructSides()
{
	Top = TileLayout[0];
	Bottom = TileLayout[TileLayout.size() - 1];

	Left = Right = "";

	for (int i = 0; i < TileLayout.size(); i++)
	{
		Left += TileLayout[i][0];
		Right += TileLayout[i][TileLayout[i].size() - 1];
	}

}

void Tile::Reset()
{
	Top = Bottom = Left = Right = "";
	TileID = -1;
	TileLayout.clear();
}
