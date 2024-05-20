#include "DXSwapChain.h"
#include "DXDeviceContext.h"
#include "DXVertexBuffer.h"
#include "DXVertexShader.h"
#include "DXPixelShader.h"
#include "AppWindow.h"

struct Vector3
{
	float X;
	float Y;
	float Z;
};

struct Vertex
{
	Vector3 Position;
	Vector3 Color;
};

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

	// 共4个顶点，前3个数字代表顶点坐标，后3个数字代表顶点颜色
	Vertex Vertices[] =
	{
		{ -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f },
		{ -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f },
		{  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.5f }
	};

	UINT VertexCount = ARRAYSIZE(Vertices);

	VertexBuffer = GraphicsEngine::Instance()->CreateVertexBuffer();

	void* ShaderBytecode = nullptr;
	SIZE_T BytecodeLength = 0;

	// 创建顶点着色器
	GraphicsEngine::Instance()->CompileVertexShader(L"./Shaders/VertexShader.hlsl","vsmain",&ShaderBytecode,&BytecodeLength);
	VertexShader = GraphicsEngine::Instance()->CreateVertexShader(ShaderBytecode, BytecodeLength);
	
	// 初始化顶点缓冲区
	VertexBuffer->Init(Vertices, sizeof(Vertex), VertexCount, ShaderBytecode, BytecodeLength);

	GraphicsEngine::Instance()->ReleaseCompiledShader();

	// 创建片元着色器
	GraphicsEngine::Instance()->CompilePixelShader(L"./Shaders/PixelShader.hlsl", "psmain", &ShaderBytecode, &BytecodeLength);
	PixelShader = GraphicsEngine::Instance()->CreatePixelShader(ShaderBytecode, BytecodeLength);

	GraphicsEngine::Instance()->ReleaseCompiledShader();
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	ImmediateContext->ClearRenderTarget(SwapChain, 0, 1, 0.5, 1);

	RECT rc = GetClientRect();
	ImmediateContext->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	ImmediateContext->SetVertexShader(VertexShader);
	ImmediateContext->SetPixelShader(PixelShader);

	ImmediateContext->SetVertexBuffer(VertexBuffer);

	ImmediateContext->DrawTriangleStrip(VertexBuffer->GetVertexCount(), 0);

	SwapChain->Present(true);
}

void AppWindow::OnDestory()
{
	Window::OnDestory();

	VertexBuffer->Release();
	SwapChain->Release();

	VertexShader->Release();
	PixelShader->Release();

	GraphicsEngine::Instance()->Release();
}
