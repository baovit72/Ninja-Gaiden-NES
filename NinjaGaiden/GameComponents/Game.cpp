#include "Game.h"
#include "Debug.h"
#include <stdlib.h>
Game * Game::__instance = NULL;
HINSTANCE Game::hInstance = NULL;
//Khởi tạo game chính
void Game::Init()
{
	hInstance = GetModuleHandle(NULL);
	
	this->hWnd = CreateGameWindow(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);

	graphics = Graphics::GetInstance();
	graphics->Init(hWnd);

	keyboard = Keyboard::GetInstance();
	keyboard->InitKeyboard(hWnd);

	LoadResources();
	OutputDebugString(L"[INFO] InitGame done;\n");
}
HWND Game::CreateGameWindow(HINSTANCE hInstance, int ScreenWidth, int ScreenHeight)
{
	//Lớp cửa sổ
	WNDCLASSEX wc;
	//Thông số lớp cửa sổ
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;
	//Đăng kí lớp cửa sổ
	RegisterClassEx(&wc);
	DWORD wflags = WS_OVERLAPPEDWINDOW;
	RECT rect;
	rect.left = rect.top = 0;
	rect.right = ScreenWidth;
	rect.bottom = ScreenHeight;
	AdjustWindowRect(&rect, wflags, false);
	//Tạo cửa sổ
	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			wflags, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			hInstance,
			NULL);
	//Kiểm tra lỗi khi tạo
	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}
	//Hiện cửa sổ lên màn hình
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return hWnd;
}
void Game::LoadResources()
{
	if (ninja == NULL) 
		ninja = Ninja::GetInstance();
	if (tiledMap == NULL)
		tiledMap = TiledMap::GetInstance(TILES_MATRIX);
	if (viewport == NULL)
		viewport = Viewport::GetInstance();
	if (grid == NULL)
		grid = Grid::GetInstance();
}
//Xử lí
void Game::Update(DWORD dt)
{
	keyboard->Update();
	grid->Update(dt);
	viewport->Update(dt);
}
void Game::Render()
{
	//Lấy thông tin các đối tượng cần thiết từ game chính
	LPDIRECT3DDEVICE9 d3ddv = graphics->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = graphics->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = graphics->GetSpriteHandler();


	//Bắt đầu render
	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		//Tô màu backbuffer
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		//Bắt đầu xử lí sprite
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		grid->Render();

		//Kết thúc xử lí sprite
		spriteHandler->End();
		//Kết thúc render
		d3ddv->EndScene();
	}

	auto start = std::chrono::steady_clock::now();
	//Hiển thị backbuffer lên màn hình
	d3ddv->Present(NULL, NULL, NULL, NULL);

	// record end time
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = (end - start) * 1000;
}
int Game::Run()
{
	if (!initialized)
	{
		Init();
		initialized = true;
	}
	//Tạo message
	MSG msg;
	int done = 0;
	//Thời gian frame hiện tại bắt đầu
	DWORD frameStart = GetTickCount();
	//Tính thời gian của mỗi frame xuất hiện trên màn hình
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	//Vòng lặp xử lí message
	while (!done)
	{
		//Tìm message thoát chương trình
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Lấy giá trị thời gian hiện tại
		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		//Tính giá trị delta time = thời gian hiện tại - thời gian bắt đầu frame trước
		DWORD dt = now - frameStart;
		//Nếu dt > tickPerFram, hay đến lúc xử lí frame tiếp theo, bắt đầu Update và Render
		/*if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else //Ngược lại, chờ đến khi đủ thời gian xử lí frame tiếp theo
		{
			Sleep(tickPerFrame - dt);
			dt = tickPerFrame;
			frameStart = now;
			Update(dt);
			Render();
		}*/
		if (dt < tickPerFrame)
		{
			Sleep(tickPerFrame - dt);
			dt = tickPerFrame;
		}
		frameStart = now;

		if (dt - tickPerFrame > 3)
			dt = tickPerFrame;

		Update(dt);

		Render();
	}

	return 1;
}

bool AABB(const Collider &c1, const Collider &c2)
{
	return (
		c1.x < c2.x + c2.width &&
		c1.x + c1.width > c2.x &&
		c1.y > c2.y - c2.height &&
		c1.y - c1.height < c2.y
		);
}
Collider GetSweptBroadphaseRect(const Collider &object)
{
	Collider broadphaseBox;
	broadphaseBox.x = object.vx > 0 ? object.x : object.x + object.vx * object.dt;
	broadphaseBox.y = object.vy > 0 ? object.y + object.vy * object.dt : object.y;
	broadphaseBox.width = object.width + abs(object.vx * object.dt);
	broadphaseBox.height = object.height + abs(object.vy * object.dt);

	return broadphaseBox;
}
float Game::SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly)
{
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	c1.vx = c1.vx - c2.vx;
	c1.vy = c1.vy - c2.vy;

	int dx = c1.vx * c1.dt;
	int dy = c1.vy * c1.dt;

	
	Collider broadphaseBox = GetSweptBroadphaseRect(c1);
	if (AABB(broadphaseBox, c2))
	{
		int i = 0;
	}
	if (!AABB(broadphaseBox, c2))
	{
		return 1.0f;
	}

	if (dx > 0.0f)
	{
		dxEntry = c2.x - (c1.x + c1.width);
		dxExit = (c2.x + c2.width) - c1.x;
	}
	else
	{
		dxEntry = (c2.x + c2.width) - c1.x;
		dxExit = c2.x - (c1.x + c1.width);
	}

	if (dy > 0.0f)
	{
		dyEntry = (c2.y - c2.height) - c1.y;
		dyExit = c2.y - (c1.y - c1.height);
	}
	else
	{
		dyEntry = c2.y - (c1.y - c1.height);
		dyExit = (c2.y - c2.height) - c1.y;
	}

	float txEntry, tyEntry;
	float txExit, tyExit;

	if (dx == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / dx;
		txExit = dxExit / dx;
	}

	if (dy == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / dy;
		tyExit = dyExit / dy;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		if (txEntry > tyEntry)
		{
			if (dxEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else if (dxEntry > 0.0f)
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
			else
			{
				if (c1.x <= c2.x)
				{
					normalx = -1.0f;
					normaly = 0.0f;
				}
				else
				{
					normalx = 1.0f;
					normaly = 0.0f;
				}
			}
		}
		else
		{
			if (dyEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else if (dyEntry > 0.0f)
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
			else
			{
				if (c1.y <= c2.y)
				{
					normalx = 0.0f;
					normaly = -1.0f;
				}
				else
				{
					normalx = 0.0f;
					normaly = 1.0f;
				}
			}
		}
		return entryTime;
	}
}

Game::~Game()
{

}
Ninja * Game::GetNinja()
{
	return ninja;
}
//Hàm lấy đối tượng
Game *Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}

LRESULT CALLBACK Game::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0); //Nếu message là WM_DESTROY thì thoát
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}