#pragma once

#include <d3d11.h>

class DXDeviceContext;

class DXConstantBuffer
{
public:
	DXConstantBuffer();
	~DXConstantBuffer();

	bool Init(void* Buffer, UINT BufferSize);
	bool Release();
	void Update(DXDeviceContext* DeviceContext,void* Buffer);

private:
	ID3D11Buffer* D3D11Buffer;

private:
	friend class DXDeviceContext;
};

