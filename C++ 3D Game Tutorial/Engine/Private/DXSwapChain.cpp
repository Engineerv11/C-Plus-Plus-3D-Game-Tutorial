#include "GraphicsEngine.h"
#include "DXSwapChain.h"

DXSwapChain::DXSwapChain()
{
}

DXSwapChain::~DXSwapChain()
{
}

bool DXSwapChain::Init(HWND WinID, UINT Width, UINT Height)
{
	ID3D11Device* Device = GraphicsEngine::Instance()->D3D11Device;

	DXGI_SWAP_CHAIN_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = Width;
	desc.BufferDesc.Height = Height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = WinID;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT Result = GraphicsEngine::Instance()->DXGIFactory->CreateSwapChain(Device, &desc, &DXGISwapChain);

	if (FAILED(Result))
	{
		return false;
	}

	return true;
}

bool DXSwapChain::Release()
{
	DXGISwapChain->Release();

	delete this;

	return true;
}
