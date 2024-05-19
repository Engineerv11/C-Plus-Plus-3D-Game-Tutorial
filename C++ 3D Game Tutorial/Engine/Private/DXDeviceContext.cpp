#include "DXSwapChain.h"
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

bool DXDeviceContext::ClearRenderTarget(DXSwapChain* SwapChain, float Red, float Green, float Blue, float Alpha)
{
	FLOAT Color[] = { Red, Green, Blue, Alpha };

	DeviceContext->ClearRenderTargetView(SwapChain->RenderTargetView, Color);

	return true;
}
