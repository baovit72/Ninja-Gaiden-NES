#include"Grid.h"
#include"Cell.h"

Grid * Grid::__instance = NULL;
bool CellGameObjectAABB(Cell * cell, GameObject * obj)
{
	return (
		cell->GetPositionX() < obj->GetPositionX() + obj->GetWidth() &&
		cell->GetPositionX() + GRID_SIZE > obj->GetPositionX() &&
		cell->GetPositionY() > obj->GetPositionY() - obj->GetHeight() &&
		cell->GetPositionY() - GRID_SIZE < obj->GetPositionY()
		);
}
bool CellTileAABB(Cell * cell, Tile & tile)
{
	return (
		cell->GetPositionX() < tile.x + tile.width &&
		cell->GetPositionX() + GRID_SIZE > tile.x &&
		cell->GetPositionY() > tile.y - tile.height &&
		cell->GetPositionY() - GRID_SIZE < tile.y
		);
}

Grid::Grid()
{
	//khoi tao danh sach cac o trong
	this->width = (int)(Game::GetInstance()->GetTiledMap()->GetWidth() / 64) + 2;
	this->height = (int)(Game::GetInstance()->GetTiledMap()->GetHeight() / 64) + 2;

	for (int i = 0; i < height; i++)
	{
		CellRow curRow;
		for (int j = 0; j < width; j++)
		{
			Cell * curCell = new Cell(j, i);
			curRow.push_back(curCell);
		}
		cells.push_back(curRow);
	}

	LoadCells();

	//Luu viewport
	this->viewport = Viewport::GetInstance();
	//Lưu ninja
	this->ninja = Ninja::GetInstance();
}

void Grid::LoadCells() 
{
	Matrix &tiledMapMatrix = Game::GetInstance()->GetTiledMap()->GetMatrix();
	for (int i = 0; i < tiledMapMatrix.size(); i++)
	{
		for (int j = 0; j < tiledMapMatrix[i].size(); j++)
		{
			//Tim vi tri o chua tile
			int cellX = POSXTOCELL(tiledMapMatrix[i][j].x);
			int cellY = POSYTOCELL(tiledMapMatrix[i][j].y);

			Tile * dummyPtr = &tiledMapMatrix[i][j];
			cells[cellY][cellX]->AddTile(dummyPtr);
		}
	}
	// Load Object
	// ---> Place holder
	// ...
}

void Grid::GetCameraPosOnGrid(int &l, int &r, int &t, int &b) {
	RECT rect = viewport->GetRect();
	l = (int)(rect.left/GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top/GRID_SIZE - 1 : rect.top/GRID_SIZE);
	r =(int)(rect.right / GRID_SIZE);
	b =(int)(rect.bottom / GRID_SIZE);
}

void Grid::GetNinjaPosOnGrid(int &l, int &r, int &t, int &b)
{
	RECT rect = ninja->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}
void Grid::Update(DWORD dt)
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);

	//Update ninja
	curTiles.clear();
	curGameObjects.clear();

	int ninjaLCell, ninjaRCell, ninjaTCell, ninjaBCell;
	this->GetNinjaPosOnGrid(ninjaLCell, ninjaRCell, ninjaTCell, ninjaBCell);
	for (int i = ninjaBCell; i <= ninjaTCell; i++)
	{
		for (int j = ninjaLCell; j <= ninjaRCell; j++)
		{
			cells[i][j]->ExtractTiles(curTiles);
			cells[i][j]->ExtractGameObjects(curGameObjects);
			//Kiểm tra với các đối tượng khác thuộc các cell lân cận
			if (j > lCell)
			{
				cells[i][j - 1]->ExtractTiles(curTiles);
				cells[i][j - 1]->ExtractGameObjects(curGameObjects);
				if (i > bCell)
				{
					cells[i - 1][j - 1]->ExtractTiles(curTiles);
					cells[i - 1][j - 1]->ExtractGameObjects(curGameObjects);
				}
				if (i < tCell)
				{
					cells[i + 1][j - 1]->ExtractTiles(curTiles);
					cells[i + 1][j - 1]->ExtractGameObjects(curGameObjects);
				}
			}
			if (j < rCell)
			{
				cells[i][j + 1]->ExtractTiles(curTiles);
				cells[i][j + 1]->ExtractGameObjects(curGameObjects);
				if (i > bCell)
				{
					cells[i - 1][j + 1]->ExtractTiles(curTiles);
					cells[i - 1][j + 1]->ExtractGameObjects(curGameObjects);
				}
				if (i < tCell)
				{
					cells[i + 1][j + 1]->ExtractTiles(curTiles);
					cells[i + 1][j + 1]->ExtractGameObjects(curGameObjects);
				}
			}
		}
	}
	ninja->Update(dt);

	////Update các object trong các cell
	//for (int i = bCell; i <= tCell; i++)
	//{		
	//	for (int j = lCell; j <= rCell; j++)
	//	{
	//		curTiles.clear();
	//		curGameObjects.clear();


	//		//Kiểm tra với các đối tượng khác thuộc các cell lân cận
	//		if (j > lCell)
	//		{
	//			cells[i][j - 1]->ExtractTiles(curTiles);
	//			cells[i][j - 1]->ExtractGameObjects(curGameObjects);
	//			if (i > bCell)
	//			{
	//				cells[i - 1][j - 1]->ExtractTiles(curTiles);
	//				cells[i - 1][j - 1]->ExtractGameObjects(curGameObjects);
	//			}
	//			if (i < tCell)
	//			{
	//				cells[i + 1][j - 1]->ExtractTiles(curTiles);
	//				cells[i + 1][j - 1]->ExtractGameObjects(curGameObjects);
	//			}
	//		}
	//		if (j < rCell)
	//		{
	//			cells[i][j + 1]->ExtractTiles(curTiles);
	//			cells[i][j + 1]->ExtractGameObjects(curGameObjects);
	//			if (i > bCell)
	//			{
	//				cells[i - 1][j + 1]->ExtractTiles(curTiles);
	//				cells[i - 1][j + 1]->ExtractGameObjects(curGameObjects);
	//			}
	//			if (i < tCell)
	//			{
	//				cells[i + 1][j + 1]->ExtractTiles(curTiles);
	//				cells[i + 1][j + 1]->ExtractGameObjects(curGameObjects);
	//			}
	//		}

	//		cells[i][j]->Update(dt);
	//	}
	//}
}
void Grid::Render()
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);
	curTiles.clear();
	curGameObjects.clear();


	for (int i = bCell; i <= tCell; i++)
	{
		for (int j = lCell; j <= rCell; j++)
		{
			cells[i][j]->Render();
		}
	}

	ninja->Render();

}

Grid * Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}



//
//
//void Unit::Update_GridInfo() {
//	//Cap nhat lai vi tri cua doi tuong trong grid
//	grid_->update_unit(this, this->object->GetPositionX(), this->object->GetPositionY());
//}
//
//
//
//void Grid::add(Unit *unit) {
//	//Tim vi tri o chua object
//	int cellX = POSTOCELL(unit->x_);
//	int cellY = POSTOCELL(unit->y_);
//	//Dua object vo cell
//	unit->prev_ = NULL;
//	unit->next_ = cells_[cellX][cellY];
//	cells_[cellX][cellY] = unit;
//	if (unit->next_ != NULL)
//		unit->next_->prev_ = unit;
//}
//void Grid::getCameraPosOnGrid(int &l, int &r, int &t, int &b) {
//	RECT rect = viewport->getRect();
//	l = POSTOCELL(rect.left);
//	t = POSTOCELL(rect.top);
//	r = POSTOCELL(rect.right);
//	b = POSTOCELL(rect.bottom);
//}
//void Grid::getObjList(vector<GameObject*>*list) {
//	//Clear danh sach objects
//	list->clear();
//	//Lay nhung shell gioi han trong camera
//	int lCell, rCell, tCell, bCell;
//	this->getCameraPosOnGrid(lCell, rCell, tCell, bCell);
//	//Duyet qua nhung cell trong viewport va tra lai danh sach cac object cua nhung cell do
//	//For rendering and updating objects in viewport
//	for (int i = lCell; i <= rCell; i++)
//		for (int j = bCell; j <= tCell; j++) {
//			Unit *currentUnit = cells_[i][j];
//			while (currentUnit != NULL) {
//				list->push_back(currentUnit->object);
//				currentUnit = currentUnit->next_;
//			}
//
//		}
//}
//void Grid::update_unit(Unit * unit, double x, double y) {
//	//Lay thong tin vi tri cu cua object
//	int oldCellX = POSTOCELL(unit->x_);
//	int oldCellY = POSTOCELL(unit->y_);
//	//Vi tri hien tai cua object trong grid
//	int cellX = POSTOCELL(x);
//	int cellY = POSTOCELL(y);
//
//	unit->x_ = x;
//	unit->y_ = y;
//
//	//Kiem tra co can di chuyen cell ?!
//	if (oldCellX == cellX && oldCellY == cellY)
//		return;
//	//Tien hanh di chuyen
//	if (unit->prev_ != NULL)
//		unit->prev_->next_ = unit->next_;
//	if (cells_[oldCellX][oldCellY] == unit)
//		cells_[oldCellX][oldCellY] = unit->next_;
//
//	if (unit->next_ != NULL)
//		unit->next_->prev_ = unit->prev_;
//
//
//	add(unit);
//	DebugOut(L"[%d,%d]->[%d,%d]\n", oldCellX, oldCellY, cellX, cellY);
//}
//
//void Grid::getUnitList(vector<Unit*>* list) {
//	//Clear list 
//	list->clear();
//
//	int lCell, rCell, tCell, bCell;
//	this->getCameraPosOnGrid(lCell, rCell, tCell, bCell);
//	for (int i = lCell; i <= rCell; i++)
//		for (int j = bCell; j <= tCell; j++) {
//			Unit * currentUnit = cells_[i][j];
//			while (currentUnit != NULL) {
//				list->push_back(currentUnit);
//				//currentUnit->Update_GridInfo(); 
//				currentUnit = currentUnit->next_;
//			}
//		}
//}
//void Grid::update() {
//
//	//DebugOut(L"[%d,%d]->[%d,%d]\n", lCell, bCell, rCell, tCell);
//	//Duyet qua nhung cell trong viewport va lay cac Units trong tung cell
//	//For updating objects' position in grid
//	vector<Unit*> units;
//	this->getUnitList(&units);
//
//	//Cập nhât toạ độ grid cho objects
//	for (int i = 0; i < units.size(); i++)
//		units.at(i)->Update_GridInfo();
//
//
//}
//void Grid::colliOnCell(Unit *unit, Unit *other) {
//	//DebugOut(L"Detecting Collisions ..... !\n");
//	while (other != NULL) {
//		//Ví dụ hàm kiểm tra va chạm ở đây 
//		//unit->object->getCollider()->detectCollision(other->object->getRECT);
//
//		other = other->next_;
//	}
//}
//void Grid::detectCollision() {
//	int lCell, rCell, tCell, bCell;
//	this->getCameraPosOnGrid(lCell, rCell, tCell, bCell);
//	for (int i = lCell; i <= rCell; i++)
//		for (int j = bCell; j <= tCell; j++) {
//			Unit *unit = cells_[i][j];
//			while (unit != NULL) {
//				//Kiểm tra va chạm với các đối tượng khác cùng cell
//				colliOnCell(unit, unit->next_);
//				//Kiểm tra va chạm với các đối tượng khác thuộc các cell lân cận (3 lân cận bên trái, 1 ô lân cận bên trên/dưới)
//				if (i > lCell & j > bCell)
//					colliOnCell(unit, cells_[i - 1][j - 1]);
//				if (i > lCell)
//					colliOnCell(unit, cells_[i - 1][j]);
//				if (j > bCell)
//					colliOnCell(unit, cells_[i][j - 1]);
//				if (i > lCell & j < tCell)
//					colliOnCell(unit, cells_[i - 1][j + 1]);
//				//Đến đối tượng tiếp theo trong ô
//				unit = unit->next_;
//			}
//		}
//
//}