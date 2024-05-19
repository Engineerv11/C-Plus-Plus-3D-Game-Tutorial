#pragma once

#include <d3d11.h>

class DXSwapChain;

class DXDeviceContext
{
public:
	DXDeviceContext(ID3D11DeviceContext* InDeviceContext);
	~DXDeviceContext();

	bool Release();
	
	bool ClearRenderTarget(DXSwapChain* SwapChain, float Red, float Green, float Blue, float Alpha);

private:
	ID3D11DeviceContext* DeviceContext;
};

