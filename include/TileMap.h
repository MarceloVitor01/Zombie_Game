#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <vector>
#include <string>

class TileMap : public Component
{
public:
    TileMap(GameObject &associated, std::string file, TileSet *tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet *tileSet);
    int &At(int x, int y, int z = 0);

    void Update(float dt) override;
    void Render() override;
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth();
    int GetHeight();
    int GetDepth();
    bool Is(std::string type) override;

private:
    std::vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif