#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    dummyObj = new GameObject();
    tileSet = new Sprite(*dummyObj, file);

    if (tileSet->IsOpen())
    {
        columns = tileSet->GetWidth() / tileWidth;
        rows = tileSet->GetHeight() / tileHeight;
    }
    else
    {
        columns = 0;
        rows = 0;
    }
}

TileSet::~TileSet()
{
    delete tileSet;
    delete dummyObj;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    if (index < (unsigned)(rows * columns))
    {
        int clipX = (index % columns) * tileWidth;
        int clipY = (index / columns) * tileHeight;

        tileSet->SetClip(clipX, clipY, tileWidth, tileHeight);
        tileSet->Render(x, y);
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}