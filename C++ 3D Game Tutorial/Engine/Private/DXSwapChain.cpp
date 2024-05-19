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

	HRESULT result = GraphicsEngine::Instance()->DXGIFactory->CreateSwapChain(Device, &desc, &DXGISwapChain);

	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* Surface = nullptr;
	result = DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&Surface));

	if (FAILED(result))
	{
		return false;
	}

	result = Device->CreateRenderTargetView(Surface, NULL, &RenderTargetView);
	Surface->Release();

	if (FAILED(result))
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

bool DXSwapChain::Present(UINT SyncInterval)
{
	DXGISwapChain->Present(SyncInterval, NULL);

	return true;
}
