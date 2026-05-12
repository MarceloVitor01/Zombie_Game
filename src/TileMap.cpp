#include "TileMap.h"
#include "Camera.h"
#include <fstream>
#include <string>

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet)
    : Component(associated), tileSet(tileSet)
{
    Load(file);
}

void TileMap::Load(std::string file)
{
    std::ifstream f(file);
    if (!f.is_open())
        return;

    std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();

    std::vector<int> numbers;
    std::string currentNumber = "";

    for (char c : content)
    {
        if ((c >= '0' && c <= '9') || (c == '-' && currentNumber.empty()))
        {
            currentNumber += c;
        }
        else if (!currentNumber.empty())
        {
            numbers.push_back(std::stoi(currentNumber));
            currentNumber = "";
        }
    }

    if (!currentNumber.empty())
    {
        numbers.push_back(std::stoi(currentNumber));
    }

    if (numbers.size() >= 3)
    {
        mapWidth = numbers[0];
        mapHeight = numbers[1];
        mapDepth = numbers[2];

        tileMatrix.clear();
        for (size_t i = 3; i < numbers.size(); i++)
        {
            tileMatrix.push_back(numbers[i]);
        }
    }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z)
{
    return tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

void TileMap::Update(float dt) {}

void TileMap::Render()
{
    for (int z = 0; z < mapDepth; z++)
    {
        RenderLayer(z, Camera::pos.x, Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            int index = At(x, y, layer);
            if (index >= 0)
            {
                float parallax = 1.0f + (layer * 0.5f);
                float posX = (x * tileSet->GetTileWidth()) - (cameraX * parallax) + associated.box.x;
                float posY = (y * tileSet->GetTileHeight()) - (cameraY * parallax) + associated.box.y;
                tileSet->RenderTile(index, posX, posY);
            }
        }
    }
}

int TileMap::GetWidth() { return mapWidth; }

int TileMap::GetHeight() { return mapHeight; }

int TileMap::GetDepth() { return mapDepth; }

bool TileMap::Is(std::string type)
{
    return type == "TileMap";
}