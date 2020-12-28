#include "TileMap.h"

int main()
{
    TileMap MyTileMap;
    if (!MyTileMap.ConstuctTileMap("input.txt")) 
    {
        return -1;
    }

    std::cout<< "P1: Answer = " << MyTileMap.GetCornersIDMulti() << std::endl;

}
