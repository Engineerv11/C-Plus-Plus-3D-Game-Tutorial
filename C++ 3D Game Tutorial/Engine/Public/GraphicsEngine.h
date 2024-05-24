#pragma once

#include <d3d11.h>

class DXSwapChain;
class DXDeviceContext;
class DXVertexBuffer;
class DXConstantBuffer;
class DXVertexShader;
class DXPixelShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init();
	bool Release();

	bool CompileVertexShader(const wchar_t* FileName, const char* EntryPoint, void** ShaderBytecode, SIZE_T* BytecodeLength);
	bool CompilePixelShader(const wchar_t* FileName, const char* EntryPoint, void** ShaderBytecode, SIZE_T* BytecodeLength);
	void ReleaseCompiledShader();

	DXSwapChain* CreateSwapChain();
	DXDeviceContext* GetImmediateContext();
	DXVertexBuffer* CreateVertexBuffer();
	DXConstantBuffer* CreateConstantBuffer();
	DXVertexShader* CreateVertexShader(const void* ShaderBytecode,SIZE_T BytecodeLength);
	DXPixelShader* CreatePixelShader(const void* ShaderBytecode, SIZE_T BytecodeLength);

public:
	static GraphicsEngine* Instance();

private:
	ID3D11Device* D3D11Device;
	IDXGIDevice* DXGIDevice;
	IDXGIAdapter* DXGIAdapter;
	IDXGIFactory* DXGIFactory;
	D3D_FEATURE_LEVEL FeatureLevel;
	DXDeviceContext* ImmediateContext;

private:
	ID3DBlob* Blob = nullptr;
	ID3DBlob* VSBlob = nullptr;
	ID3DBlob* PSBlob = nullptr;

	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;

private:
	friend class DXSwapChain;
	friend class DXVertexBuffer;
	friend class DXConstantBuffer;
	friend class DXVertexShader;
	friend class DXPixelShader;
};

