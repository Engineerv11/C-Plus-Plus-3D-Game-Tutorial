#pragma once

#include <d3d11.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init();
	bool Release();
public:
	static GraphicsEngine* Instance();

private:
	ID3D11Device* D3D11Device;
	ID3D11DeviceContext* ImmediateContext;
	D3D_FEATURE_LEVEL FeatureLevel;
};

