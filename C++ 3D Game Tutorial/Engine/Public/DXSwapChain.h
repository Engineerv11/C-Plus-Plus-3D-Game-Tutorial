#pragma once

#include <d3d11.h>

class DXDeviceContext;

class DXSwapChain
{
public:
	DXSwapChain();
	~DXSwapChain();

	bool Init(HWND WinID, UINT Width, UINT Height);
	bool Release();

	bool Present(UINT SyncInterval);
	
private:
	IDXGISwapChain* DXGISwapChain;
	ID3D11RenderTargetView* RenderTargetView;

private:
	friend class DXDeviceContext;
};

