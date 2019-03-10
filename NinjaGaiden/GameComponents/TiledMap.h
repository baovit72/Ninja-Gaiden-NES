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
#include "Constants.h"

using namespace std;

typedef vector<vector <int>> Matrix;
typedef vector<int> Row;
class TiledMap
{
private:
	void LoadMap(LPCWSTR filePath);
	string LoadMatrix(LPCWSTR filePath);
	void LoadTileSet(LPCWSTR tilesLocation);
	Matrix matrix;

	int tileSetWidth, tileSetHeight;
	LPCWSTR infoLocation;
	unordered_map<int, Sprite*> tiles;
public:
	TiledMap(LPCWSTR filePath);

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void Render();

	~TiledMap();
};