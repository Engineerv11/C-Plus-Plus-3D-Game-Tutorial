#include "GraphicsEngine.h"
#include "DXPixelShader.h"

DXPixelShader::DXPixelShader()
{
}

DXPixelShader::~DXPixelShader()
{
}

bool DXPixelShader::Init(const void* ShaderBytecode, SIZE_T BytecodeLength)
{
	HRESULT result;

	result = GraphicsEngine::Instance()->D3D11Device->CreatePixelShader(ShaderBytecode, BytecodeLength, nullptr, &D3D11PixelShader);

	if (!SUCCEEDED(result))
	{
		return false;
	}

	return true;
}

bool DXPixelShader::Release()
{
	D3D11PixelShader->Release();
	delete this;

	return true;
}
