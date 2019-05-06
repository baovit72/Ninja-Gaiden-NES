#include "Cell.h"
#include "Grid.h"


void Cell::ExtractTiles(vector<Tile *> &output)
{
	output.insert(output.end(), this->tiles.begin(), this->tiles.end());
}

void Cell::ExtractGameObjects(vector<GameObject *> &output)
{
	output.insert(output.end(), this->gameObjects.begin(), this->gameObjects.end());
}

void Cell::Update(DWORD dt)
{
	return;
}
void Cell::Render()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		TiledMap::GetInstance()->RenderTile(tiles[i]);
	}
}

Cell::~Cell()
{
}
