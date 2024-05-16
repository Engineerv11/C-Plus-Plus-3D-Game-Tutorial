#include <Windows.h>

#include "Window.h"

Window* window = nullptr;

Window::Window()
{
}

Window::~Window()
{
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		Window* window = reinterpret_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->SetWinID(hWnd);

		window->OnCreate();
		break;
	}
	case WM_DESTROY:
	{
		window->OnDestory();
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	}

	return NULL;
}

void Window::OnDestory()
{
	bIsRuning = false;
}

bool Window::Init()
{
	WNDCLASSEX wc;
	
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"D3D11 Window";
	wc.lpszMenuName = NULL;
	wc.style = NULL;
	wc.lpfnWndProc = WindowProc;

	if (!RegisterClassExW(&wc))
	{
		return false;
	}

	if (!window)
	{
		window = this;
	}

	WinID = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, wc.lpszClassName, L"D3D11 Window", 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!WinID)
	{
		return false;
	}

	ShowWindow(WinID, SW_SHOW);

	UpdateWindow(WinID);

	bIsRuning = true;

	return true;
}

bool Window::Release()
{
	if (!DestroyWindow(WinID))
	{
		return false;
	}

	return true;
}

bool Window::Broadcast()
{
	MSG msg;

	while (PeekMessage(&msg,NULL,0,0,PM_REMOVE)>0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	window->OnUpdate();

	Sleep(0);

	return true;
}

bool Window::IsRuning()
{
	return bIsRuning;
}

void Window::SetWinID(HWND InWinID)
{
	WinID = InWinID;
}

RECT Window::GetClientRect()
{
	RECT rc;
	::GetClientRect(WinID, &rc);
	return rc;
}
