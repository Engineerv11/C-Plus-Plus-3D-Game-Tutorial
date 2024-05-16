#pragma once

#include <d3d11.h>

class DXSwapChain
{
public:
	DXSwapChain();
	~DXSwapChain();

	bool Init(HWND WinID, UINT Width, UINT Height);
	bool Release();
	
private:
	IDXGISwapChain* DXGISwapChain;
};

