#pragma once

#include <d3d11.h>

class DXSwapChain;
class DXVertexBuffer;
class DXVertexShader;
class DXPixelShader;

class DXDeviceContext
{
public:
	DXDeviceContext(ID3D11DeviceContext* InDeviceContext);
	~DXDeviceContext();

	bool Release();
	
	void ClearRenderTarget(DXSwapChain* SwapChain, float Red, float Green, float Blue, float Alpha);
	void SetVertexBuffer(DXVertexBuffer* VertexBuffer);
	void DrawTriangleList(UINT VertexCount, UINT StartVertexLocation);
	void DrawTriangleStrip(UINT VertexCount, UINT StartVertexLocation);
	void SetViewportSize(UINT Width, UINT Height);
	void SetVertexShader(DXVertexShader* VertexShader);
	void SetPixelShader(DXPixelShader* PixelShader);

private:
	ID3D11DeviceContext* DeviceContext;
};

