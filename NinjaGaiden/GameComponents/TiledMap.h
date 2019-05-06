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
#include "GameObject.h"
using namespace std;


const vector<int> _31SolidIds { 24, 25, 26, 39, 58, 63, 65, 69, 70, 71 };

struct Tile {
	int tileId;
	int type; // 0 = background, 1 = solid
	int x, y;
	int width = 16, height = 16;
};

typedef GameObject * SolidTile;

typedef vector<SolidTile> SolidTileSet;

typedef vector<Tile> Row;
typedef vector<Row> Matrix;

class TiledMap
{
private:
	static TiledMap * __instance;
	TiledMap(LPCWSTR filePath);

	void LoadMap(LPCWSTR filePath);
	string LoadMatrix(LPCWSTR filePath);
	void LoadTileSet(LPCWSTR tilesLocation);

	Row GetMatrixRow(int lineNum, string line, string delimiter);

	Matrix matrix;

	int mapWidth, mapHeight;
	int tileSetWidth, tileSetHeight;
	LPCWSTR infoLocation;

	unordered_map<int, Sprite *> tileSet;
public:
	static TiledMap * GetInstance(LPCWSTR filePath = NULL);

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	Matrix & GetMatrix() { return matrix; }


	void Update(DWORD dt);
	void Render();

	void RenderTile(Tile * curTile);

	~TiledMap();
};