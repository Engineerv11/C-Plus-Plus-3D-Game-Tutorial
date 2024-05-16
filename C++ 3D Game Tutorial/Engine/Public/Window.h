#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestory();

	bool Init();
	bool Release();
	bool Broadcast();
	bool IsRuning();

	void SetWinID(HWND InWinID);
	RECT GetClientRect();

protected:
	HWND WinID;
	bool bIsRuning;
};

