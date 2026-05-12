#ifndef TILESET_H
#define TILESET_H

#include "Sprite.h"
#include "GameObject.h"
#include <string>

class TileSet
{
public:
    TileSet(int tileWidth, int tileHeight, std::string file);
    ~TileSet();

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();

private:
    GameObject *dummyObj;
    Sprite *tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};

#endif