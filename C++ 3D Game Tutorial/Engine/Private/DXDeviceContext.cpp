#include "DXSwapChain.h"
#include "DXVertexBuffer.h"
#include "DXVertexShader.h"
#include "DXPixelShader.h"
#include "DXDeviceContext.h"

DXDeviceContext::DXDeviceContext(ID3D11DeviceContext* InDeviceContext):DeviceContext(InDeviceContext)
{
}

DXDeviceContext::~DXDeviceContext()
{
}

bool DXDeviceContext::Release()
{
	DeviceContext->Release();
	delete this;

	return true;
}

void DXDeviceContext::ClearRenderTarget(DXSwapChain* SwapChain, float Red, float Green, float Blue, float Alpha)
{
	FLOAT Color[] = { Red, Green, Blue, Alpha };

	DeviceContext->ClearRenderTargetView(SwapChain->RenderTargetView, Color);

	DeviceContext->OMSetRenderTargets(1, &SwapChain->RenderTargetView, NULL);
}

void DXDeviceContext::SetVertexBuffer(DXVertexBuffer* VertexBuffer)
{
	UINT Stride = VertexBuffer->VertexSize;
	UINT Offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer->Buffer, &Stride, &Offset);
	DeviceContext->IASetInputLayout(VertexBuffer->InputLayout);
}

void DXDeviceContext::DrawTriangleList(UINT VertexCount, UINT StartVertexLocation)
{
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->Draw(VertexCount, StartVertexLocation);
}

void DXDeviceContext::DrawTriangleStrip(UINT VertexCount, UINT StartVertexLocation)
{
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	DeviceContext->Draw(VertexCount, StartVertexLocation);
}

void DXDeviceContext::SetViewportSize(UINT Width, UINT Height)
{
	D3D11_VIEWPORT viewport;

	ZeroMemory(&viewport, sizeof(viewport));

	viewport.Width = static_cast<FLOAT>(Width);
	viewport.Height = static_cast<FLOAT>(Height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	DeviceContext->RSSetViewports(1, &viewport);
}

void DXDeviceContext::SetVertexShader(DXVertexShader* VertexShader)
{
	DeviceContext->VSSetShader(VertexShader->D3D11VertexShader, nullptr, 0);
}

void DXDeviceContext::SetPixelShader(DXPixelShader* PixelShader)
{
	DeviceContext->PSSetShader(PixelShader->D3D11PixelShader, nullptr, 0);
}
