#include "TiledMap.h"


TiledMap::TiledMap(LPCWSTR filePath)
{
	infoLocation = filePath;
	
	LoadMap(filePath);
}
//Lấy dữ liệu đọc chuyển thành dòng trong ma trận
Row GetMatrixRow(string line, string delimiter)
{
	size_t pos = 0;
	string token;
	Row result = Row();
	while ((pos = line.find(delimiter)) != string::npos)
	{
		token = line.substr(0, pos);
		result.push_back(stoi(token));
		line.erase(0, pos + delimiter.length());
	}

	return result;
}
// -> stackoverflow.com => chuyển string thành wstring
std::wstring s2ws(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
//
void TiledMap::LoadMap(LPCWSTR filePath)
{
	string tilesLocation = LoadMatrix(filePath);

	std::wstring stemp = s2ws(tilesLocation);
	LPCWSTR wstrTilesLocation = stemp.c_str();
	LoadTileSet(wstrTilesLocation);
}
string TiledMap::LoadMatrix(LPCWSTR filePath)
{
	string tilesLocation;

	ifstream tilesInfo;
	DebugOut(L"filepath: %s\n", filePath);
	tilesInfo.open(filePath);
	if (tilesInfo.is_open())
	{
		getline(tilesInfo, tilesLocation);

		string line;
		Row matrixRow;
		this->matrix.clear();
		while (getline(tilesInfo, line))
		{
			matrixRow = GetMatrixRow(line, TILES_MATRIX_DELIMITER);
			this->matrix.push_back(matrixRow);
		}
		tilesInfo.close();
	}
	return tilesLocation;

}
void TiledMap::LoadTileSet(LPCWSTR tilesLocation)
{
	HRESULT result;
	//Thông tin tileset
	D3DXIMAGE_INFO info;
	//Lấy thông tin texture từ đường dẫn file
	result = D3DXGetImageInfoFromFile(tilesLocation, &info);
	//Kiểm tra lỗi khi lấy thông tin
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] Load Map Tileset failed: %s\n", tilesLocation);
		return;
	}
	this->tileSetWidth = info.Width / TILES_WIDTH_PER_TILE;
	this->tileSetHeight = info.Height / TILES_HEIGHT_PER_TILE;
	this->mapWidth = info.Width;
	this->mapHeight = info.Height;
	tiles[0] = 0;
	for (int i = 0; i < this->tileSetHeight * this->tileSetWidth; i++)
	{
		RECT rect;
		rect.left = (i % this->tileSetWidth) * TILES_WIDTH_PER_TILE;
		rect.right = rect.left + TILES_WIDTH_PER_TILE;
		rect.top = (i / this->tileSetWidth) * TILES_HEIGHT_PER_TILE;
		rect.bottom = rect.top + TILES_HEIGHT_PER_TILE;

		Sprite * tile = new Sprite(tilesLocation, rect, TILES_TRANSCOLOR);

		tiles[i + 1] = tile;
	}
}

TiledMap::~TiledMap()
{

}

int TiledMap::GetWidth()
{
	return mapWidth;
}
int TiledMap::GetHeight()
{
	return mapHeight;
}
int TiledMap::GetTileWidth()
{
	return this->tileSetWidth;
}
int TiledMap::GetTileHeight()
{
	return this->tileSetHeight;
}
void TiledMap::Render()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		Row curRow = matrix[i];
		for (int j = 0; j < curRow.size(); j++)
		{
			if (curRow[j] != 0)
			{
				SpriteData spriteData;
				spriteData.width = TILES_WIDTH_PER_TILE;
				spriteData.height = TILES_HEIGHT_PER_TILE;
				spriteData.x = j * TILES_WIDTH_PER_TILE;
				spriteData.y = (matrix.size() - i) * TILES_HEIGHT_PER_TILE;
				spriteData.scale = 1;
				spriteData.angle = 0;
				spriteData.isLeft = true;

				tiles.at(curRow[j])->SetData(spriteData);
				Graphics::GetInstance()->Draw(tiles.at(curRow[j]));
			}
		}
	}
}