#pragma once

#include <d3d11.h>

class GraphicsEngine;
class DXDeviceContext;

class DXVertexShader
{
public:
	DXVertexShader();
	~DXVertexShader();

	bool Init(const void* ShaderBytecode, SIZE_T BytecodeLength);
	bool Release();

private:
	ID3D11VertexShader* D3D11VertexShader;

private:
	friend class GraphicsEngine;
	friend class DXDeviceContext;
};

