#pragma once
#include "Constants.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Ninja.h"
#include "TiledMap.h"

class Graphics;
class Keyboard;

class Game
{
	bool initialized = false;

	static Game * __instance;
	static HINSTANCE hInstance;
	HWND hWnd;									//Xử lí cửa sổ

	Keyboard * keyboard;
	Graphics * graphics;

	Ninja * ninja;
	TiledMap * tiledMap;
	Viewport * viewport;
public:
	//Khởi tạo game chính
	void Init();
	HWND CreateGameWindow(HINSTANCE hInstance, int ScreenWidth, int ScreenHeight);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void LoadResources();
	//Xử lí
	void Update(DWORD dt);
	void Render();
	int Run();

	static float SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly);
	//Lấy đối tượng
	Ninja * GetNinja();
	TiledMap * GetTiledMap() { return tiledMap; }
	static Game * GetInstance();
	//Hàm hủy đối tượng
	~Game();
};


