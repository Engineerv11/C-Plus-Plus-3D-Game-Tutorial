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
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
}

void AppWindow::OnDestory()
{
	Window::OnDestory();
	GraphicsEngine::Instance()->Release();
}
