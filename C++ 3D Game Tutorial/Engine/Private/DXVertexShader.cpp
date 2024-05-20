#include "GraphicsEngine.h"
#include "DXVertexShader.h"

DXVertexShader::DXVertexShader()
{
}

DXVertexShader::~DXVertexShader()
{
}

bool DXVertexShader::Init(const void* ShaderBytecode, SIZE_T BytecodeLength)
{
	HRESULT result;
	
	result = GraphicsEngine::Instance()->D3D11Device->CreateVertexShader(ShaderBytecode, BytecodeLength, nullptr, &D3D11VertexShader);

	if (!SUCCEEDED(result))
	{
		return false;
	}

	return true;
}

bool DXVertexShader::Release()
{
	D3D11VertexShader->Release();
	delete this;

	return true;
}
