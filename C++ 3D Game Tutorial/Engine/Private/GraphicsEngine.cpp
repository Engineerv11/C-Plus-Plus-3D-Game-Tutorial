#include "DXSwapChain.h"
#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::Init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT Result = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; ++driver_type_index)
	{
		Result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels,
			D3D11_SDK_VERSION, &D3D11Device, &FeatureLevel, &ImmediateContext);

		if (SUCCEEDED(Result))
		{
			break;
		}
	}

	if (FAILED(Result))
	{
		return false;
	}

	D3D11Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGIDevice));
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DXGIAdapter));
	DXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&DXGIFactory));

	return true;
}

bool GraphicsEngine::Release()
{
	DXGIDevice->Release();
	DXGIAdapter->Release();
	DXGIFactory->Release();

	ImmediateContext->Release();
	D3D11Device->Release();

	return true;
}

DXSwapChain* GraphicsEngine::CreateSwapChain()
{
	return new DXSwapChain();
}

GraphicsEngine* GraphicsEngine::Instance()
{
	static GraphicsEngine Engine;

	return &Engine;
}
