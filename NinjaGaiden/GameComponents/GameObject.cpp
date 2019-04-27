#include "GameObject.h"
#include "Game.h"


GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	isLeft = false;
	isFlipped = false;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = 0;
	collider.height = 0;
}
GameObject::GameObject(float x, float y, float width, float height) 
{ 
	this->x = x; 
	this->y = y; 
	vx = vy = 0;
	isLeft = false;
	isFlipped = false;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = width;
	collider.height = height;
}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float t, nx, ny;

	t = Game::SweptAABB(
		this->collider,
		coO->GetCollider(),
		nx,
		ny
	);

	LPCOLLISIONEVENT e = new CollisionEvent(t, nx, ny, coO);
	return e;
}
void GameObject::CalcPotentialGameObjectCollisions(
	vector<LPGAMEOBJECT> &coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	return;
}
void GameObject::CalcPotentialMapCollisions(
	Matrix &tiledMapMatrix, 
	vector<LPCOLLISIONEVENT> &coEvents)
{

	LPGAMEOBJECT solidTileDummy = new GameObject(0, 0, 16, 16);
	for (int i = 0; i < tiledMapMatrix.size(); i++)
	{
		for (int j = 0; j < tiledMapMatrix[i].size(); j++)
		{
			Tile curTile = tiledMapMatrix[i][j];
			if (curTile.type == 1)
			{	
				solidTileDummy->SetPositionX(curTile.x);
				solidTileDummy->SetPositionY(curTile.y);
				solidTileDummy->UpdateTileCollider();

				LPCOLLISIONEVENT e = SweptAABBEx(solidTileDummy);
				e->collisionID = 1;

				if (e->t >= 0 && e->t < 1.0f && e->ny == 1)
					coEvents.push_back(e);
				else
				{
					delete e;
				}
			}
		}
	}
}

void GameObject::CalcPotentialCollisions(
	Matrix &tiledMapMatrix,
	vector<LPGAMEOBJECT> &coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	this->UpdateObjectCollider();
	CalcPotentialMapCollisions(tiledMapMatrix, coEvents);
	CalcPotentialGameObjectCollisions(coObjects, coEvents);

	sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}



GameObject::~GameObject()
{
}

//Hàm cập nhật
void GameObject::Update(DWORD dt)
{

}

void GameObject::UpdateObjectCollider()
{
	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
}
void GameObject::UpdateTileCollider()
{
	collider.x = x;
	collider.y = y - 8;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.height = 8;
}
//Hàm render
void GameObject::Render()
{

}