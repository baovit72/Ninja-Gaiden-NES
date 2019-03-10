#pragma once
#include "Game.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

#include "Constants.h"
class Keyboard
{
	static Keyboard * __instance;
	HWND hWnd;		

	LPDIRECTINPUT8       di;		//Đối tượng DirectInput8        
	LPDIRECTINPUTDEVICE8 didv;		//Đối tượng thiết bị của DirectInput8

	BYTE  keyStates[256];			//Bộ đệm trạng thái bàn phím
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		//Dữ liệu đệm bàn phím

public:
	//Khởi tạo bàn phím
	void InitKeyboard(HWND hWnd);
	void Poll_Keyboard();

	//Xử lí bàn phím
	void UpdateKeyStates();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update();
	//Kiểm tra phím được nhấn
	int IsKeyDown(int KeyCode);
	int IsKeyUp(int KeyCode);
	//Lấy đối tượng
	static Keyboard * GetInstance();
	//Hàm hủy đối tượng
	~Keyboard();
};