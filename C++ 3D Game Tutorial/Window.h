#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	virtual void OnCreate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestory();

	bool Init();
	bool Release();
	bool Broadcast();
	bool IsRuning();



protected:
	HWND WinID;
	bool bIsRuning;
};

