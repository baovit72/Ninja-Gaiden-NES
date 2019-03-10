#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <unordered_map> 
#include <iostream>
#include <fstream>
#include <string>

#include "Sprite.h"
#include "Debug.h"

#define TILES_LOCATION "..\\Resources\\TiledMap\\Tiles.png"
#define TILES_MATRIX "..\\Resources\\TiledMap\\Tiles_Matrix.txt"
#define TILES_MATRIX_DELIMITER ","
#define TILES_WIDTH_PER_TILE 16
#define TILES_HEIGHT_PER_TILE 16
#define TILES_TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)
using namespace std;

typedef vector<vector <int>> Matrix;
typedef vector<int> Row;
class TiledMap
{
public:
	TiledMap(char* filePath);

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void Render();

	~TiledMap();

private:
	void LoadMap(char* filePath);
	void LoadTileSet(string tilesLocation);
	Matrix matrix;

	int tileSetWidth, tileSetHeight;
	unordered_map<int, Sprite*> tiles;
};