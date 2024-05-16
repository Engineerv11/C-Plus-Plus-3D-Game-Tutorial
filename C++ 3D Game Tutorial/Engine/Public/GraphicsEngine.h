#pragma once

#include <d3d11.h>

class DXSwapChain;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init();
	bool Release();

	DXSwapChain* CreateSwapChain();

public:
	static GraphicsEngine* Instance();

private:
	ID3D11Device* D3D11Device;
	ID3D11DeviceContext* ImmediateContext;
	IDXGIDevice* DXGIDevice;
	IDXGIAdapter* DXGIAdapter;
	IDXGIFactory* DXGIFactory;
	D3D_FEATURE_LEVEL FeatureLevel;

private:
	friend class DXSwapChain;
};

