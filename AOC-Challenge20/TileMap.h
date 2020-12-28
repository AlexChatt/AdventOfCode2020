#pragma once

#include <fstream>

#include "Tile.h"

class TileMap
{
private:
	std::vector<Tile> MyTiles;

	void GetTopRight(std::vector<uint16_t> &CornersFound);
	void GetTopLeft(std::vector<uint16_t> &CornersFound);
	void GetBottomRight(std::vector<uint16_t> &CornersFound);
	void GetBottomLeft(std::vector<uint16_t> &CornersFound);

public:

	bool ConstuctTileMap(const std::string filename);

	uint64_t GetCornersIDMulti();

};