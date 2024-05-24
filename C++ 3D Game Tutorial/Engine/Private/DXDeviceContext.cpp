#include "DXSwapChain.h"
#include "DXVertexBuffer.h"
#include "DXConstantBuffer.h"
#include "DXVertexShader.h"
#include "DXPixelShader.h"
#include "DXDeviceContext.h"

DXDeviceContext::DXDeviceContext(ID3D11DeviceContext* InDeviceContext):D3D11DeviceContext(InDeviceContext)
{
}

DXDeviceContext::~DXDeviceContext()
{
}

bool DXDeviceContext::Release()
{
	D3D11DeviceContext->Release();
	delete this;

	return true;
}

void DXDeviceContext::ClearRenderTarget(DXSwapChain* SwapChain, float Red, float Green, float Blue, float Alpha)
{
	FLOAT Color[] = { Red, Green, Blue, Alpha };

	D3D11DeviceContext->ClearRenderTargetView(SwapChain->RenderTargetView, Color);

	D3D11DeviceContext->OMSetRenderTargets(1, &SwapChain->RenderTargetView, NULL);
}

void DXDeviceContext::SetVertexBuffer(DXVertexBuffer* VertexBuffer)
{
	UINT Stride = VertexBuffer->VertexSize;
	UINT Offset = 0;

	D3D11DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer->D3D11Buffer, &Stride, &Offset);
	D3D11DeviceContext->IASetInputLayout(VertexBuffer->InputLayout);
}

void DXDeviceContext::SetConstantBuffer(DXVertexShader* VertexShader, DXConstantBuffer* ConstantBuffer)
{
	D3D11DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer->D3D11Buffer);
}

void DXDeviceContext::SetConstantBuffer(DXPixelShader* PixelShader, DXConstantBuffer* ConstantBuffer)
{
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, &ConstantBuffer->D3D11Buffer);
}

void DXDeviceContext::DrawTriangleList(UINT VertexCount, UINT StartVertexLocation)
{
	D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11DeviceContext->Draw(VertexCount, StartVertexLocation);
}

void DXDeviceContext::DrawTriangleStrip(UINT VertexCount, UINT StartVertexLocation)
{
	D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D11DeviceContext->Draw(VertexCount, StartVertexLocation);
}

void DXDeviceContext::SetViewportSize(UINT Width, UINT Height)
{
	D3D11_VIEWPORT viewport;

	ZeroMemory(&viewport, sizeof(viewport));

	viewport.Width = static_cast<FLOAT>(Width);
	viewport.Height = static_cast<FLOAT>(Height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	D3D11DeviceContext->RSSetViewports(1, &viewport);
}

void DXDeviceContext::SetVertexShader(DXVertexShader* VertexShader)
{
	D3D11DeviceContext->VSSetShader(VertexShader->D3D11VertexShader, nullptr, 0);
}

void DXDeviceContext::SetPixelShader(DXPixelShader* PixelShader)
{
	D3D11DeviceContext->PSSetShader(PixelShader->D3D11PixelShader, nullptr, 0);
}
