#include "DXSwapChain.h"
#include "DXDeviceContext.h"
#include "DXVertexBuffer.h"
#include "DXConstantBuffer.h"
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
	Vector3 Position1;
	Vector3 Color;
	Vector3 Color1;
};

__declspec(align(16))
struct Constant
{
	unsigned int Time;
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

	// 共4个顶点，1-3代表顶点坐标，4-6代表顶点坐标，7-9代表顶点颜色，10-12代表顶点颜色
	// 绘制图形使用的实际顶点坐标将根据实时获取的系统时间在1-3和4-6表示的坐标中插值以实现动画效果，颜色计算遵行相同的规则
	Vertex Vertices[] =
	{
		{ -0.5f, -0.5f, 0.0f, -0.32f, -0.11f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, -0.11f,  0.78f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f },
		{  0.5f, -0.5f, 0.0f,  0.75f, -0.73f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f },
		{  0.5f,  0.5f, 0.0f,  0.88f,  0.77f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, 1.0f, 0.0f }
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

	Constant cst;
	cst.Time = 0;

	ConstantBuffer = GraphicsEngine::Instance()->CreateConstantBuffer();
	ConstantBuffer->Init(&cst, sizeof(Constant));
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	ImmediateContext->ClearRenderTarget(SwapChain, 0, 0, 0, 1);

	RECT rc = GetClientRect();
	ImmediateContext->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	Constant cst;
	cst.Time = GetTickCount();

	ConstantBuffer->Update(ImmediateContext, &cst);

	ImmediateContext->SetConstantBuffer(VertexShader, ConstantBuffer);
	ImmediateContext->SetConstantBuffer(PixelShader, ConstantBuffer);

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
