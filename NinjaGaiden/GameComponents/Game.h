#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Simon.h"
#include "TiledMap.h"
//Tên ứng dụng
#define WINDOW_CLASS_NAME L"Ninja Gaiden"
#define MAIN_WINDOW_TITLE L"Ninja Gaiden"
//Màu background, kích cỡ màn hình
#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 448

//Framerate tối đa
#define MAX_FRAME_RATE 90
//Id texture của các vật thể
#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

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

	Simon * simon;
	TiledMap * tiledMap;
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
	//Lấy đối tượng
	Simon * GetSimon();
	static Game * GetInstance();
	//Hàm hủy đối tượng
	~Game();
};


