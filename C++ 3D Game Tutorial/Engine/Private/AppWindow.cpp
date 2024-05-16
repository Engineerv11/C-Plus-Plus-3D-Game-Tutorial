#include "DXSwapChain.h"
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

	SwapChain = GraphicsEngine::Instance()->CreateSwapChain();

	RECT rc = GetClientRect();

	SwapChain->Init(WinID, rc.right - rc.left, rc.bottom - rc.top);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
}

void AppWindow::OnDestory()
{
	Window::OnDestory();

	SwapChain->Release();
	GraphicsEngine::Instance()->Release();
}
