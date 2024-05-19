#include "DXSwapChain.h"
#include "DXDeviceContext.h"
#include "AppWindow.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	Window::OnCreate();

	GraphicsEngine::Instance()->Init();

	ImmediateContext = GraphicsEngine::Instance()->GetImmediateContext();

	SwapChain = GraphicsEngine::Instance()->CreateSwapChain();

	RECT rc = GetClientRect();

	SwapChain->Init(WinID, rc.right - rc.left, rc.bottom - rc.top);

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	ImmediateContext->ClearRenderTarget(SwapChain, 0, 1, 0.5, 1);

	SwapChain->Present(false);
}

void AppWindow::OnDestory()
{
	Window::OnDestory();

	SwapChain->Release();
	GraphicsEngine::Instance()->Release();
}
