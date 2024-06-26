#pragma once

#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow :public Window
{
public:
	AppWindow();
	~AppWindow();

	// 通过 Window 继承
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestory() override;

private:
	DXSwapChain* SwapChain;
	DXDeviceContext* ImmediateContext;
	DXVertexBuffer* VertexBuffer;
	DXVertexShader* VertexShader;
	DXPixelShader* PixelShader;
	DXConstantBuffer* ConstantBuffer;
};

