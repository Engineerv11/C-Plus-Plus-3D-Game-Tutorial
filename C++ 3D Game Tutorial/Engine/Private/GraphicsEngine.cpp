#include <d3dcompiler.h>

#include "DXSwapChain.h"
#include "DXDeviceContext.h"
#include "DXVertexBuffer.h"
#include "DXVertexShader.h"
#include "DXPixelShader.h"
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

	HRESULT result = 0;
	ID3D11DeviceContext* DeviceContext;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; ++driver_type_index)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels,
			D3D11_SDK_VERSION, &D3D11Device, &FeatureLevel, &DeviceContext);

		if (SUCCEEDED(result))
		{
			break;
		}
	}

	if (FAILED(result))
	{
		return false;
	}

	ImmediateContext = new DXDeviceContext(DeviceContext);

	D3D11Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGIDevice));
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DXGIAdapter));
	DXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&DXGIFactory));

	return true;
}

bool GraphicsEngine::Release()
{

	if (VertexShader)VertexShader->Release();
	if (PixelShader)PixelShader->Release();
	if (VSBlob)VSBlob->Release();
	if (PSBlob)PSBlob->Release();

	DXGIDevice->Release();
	DXGIAdapter->Release();
	DXGIFactory->Release();

	ImmediateContext->Release();
	D3D11Device->Release();

	return true;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* FileName, const char* EntryPoint, void** ShaderBytecode,SIZE_T* BytecodeLength)
{
	ID3DBlob* ErrorBlob = nullptr;

	HRESULT result;

	result = D3DCompileFromFile(FileName, nullptr, nullptr, EntryPoint, "vs_5_0", 0, 0, &Blob, &ErrorBlob);

	if (!SUCCEEDED(result))
	{
		if (ErrorBlob)
		{
			ErrorBlob->Release();
		}
		return false;
	}

	*ShaderBytecode = Blob->GetBufferPointer();
	*BytecodeLength = Blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* FileName, const char* EntryPoint, void** ShaderBytecode, SIZE_T* BytecodeLength)
{
	ID3DBlob* ErrorBlob = nullptr;

	HRESULT result;

	result = D3DCompileFromFile(FileName, nullptr, nullptr, EntryPoint, "ps_5_0", 0, 0, &Blob, &ErrorBlob);

	if (!SUCCEEDED(result))
	{
		if (ErrorBlob)
		{
			ErrorBlob->Release();
		}
		return false;
	}

	*ShaderBytecode = Blob->GetBufferPointer();
	*BytecodeLength = Blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (Blob)Blob->Release();
}

DXSwapChain* GraphicsEngine::CreateSwapChain()
{
	return new DXSwapChain();
}

DXDeviceContext* GraphicsEngine::GetImmediateContext()
{
	return ImmediateContext;
}

DXVertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new DXVertexBuffer();
}

DXVertexShader* GraphicsEngine::CreateVertexShader(const void* ShaderBytecode, SIZE_T BytecodeLength)
{
	DXVertexShader* VertexShader = new DXVertexShader();

	if (!VertexShader->Init(ShaderBytecode, BytecodeLength))
	{
		VertexShader->Release();

		return nullptr;
	}

	return VertexShader;
}

DXPixelShader* GraphicsEngine::CreatePixelShader(const void* ShaderBytecode, SIZE_T BytecodeLength)
{
	DXPixelShader* PixelShader = new DXPixelShader();

	if (!PixelShader->Init(ShaderBytecode, BytecodeLength))
	{
		PixelShader->Release();

		return nullptr;
	}

	return PixelShader;
}

GraphicsEngine* GraphicsEngine::Instance()
{
	static GraphicsEngine Engine;

	return &Engine;
}
