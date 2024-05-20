#pragma once

#include <d3d11.h>

class GraphicsEngine;
class DXDeviceContext;

class DXPixelShader
{
public:
	DXPixelShader();
	~DXPixelShader();

	bool Init(const void* ShaderBytecode, SIZE_T BytecodeLength);
	bool Release();

private:
	ID3D11PixelShader* D3D11PixelShader;

private:
	friend class GraphicsEngine;
	friend class DXDeviceContext;
};

