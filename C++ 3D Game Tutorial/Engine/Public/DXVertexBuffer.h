#pragma once

#include <d3d11.h>

class DXDeviceContext;

class DXVertexBuffer
{
public:
	DXVertexBuffer();
	~DXVertexBuffer();

	bool Init(void* Vertices, UINT InVertexSize, UINT InVertexCount, void* ShaderBytecode, UINT BytecodeLength);
	bool Release();

	UINT GetVertexCount();

private:
	UINT VertexSize;
	UINT VertexCount;
	ID3D11Buffer* Buffer;
	ID3D11InputLayout* InputLayout;

private:
	friend class DXDeviceContext;
};

