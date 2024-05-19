#pragma once

#include <d3d11.h>

class DXSwapChain;
class DXDeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init();
	bool Release();

	DXSwapChain* CreateSwapChain();
	DXDeviceContext* GetImmediateContext();

public:
	static GraphicsEngine* Instance();

private:
	ID3D11Device* D3D11Device;
	IDXGIDevice* DXGIDevice;
	IDXGIAdapter* DXGIAdapter;
	IDXGIFactory* DXGIFactory;
	D3D_FEATURE_LEVEL FeatureLevel;
	DXDeviceContext* ImmediateContext;

private:
	friend class DXSwapChain;
};

