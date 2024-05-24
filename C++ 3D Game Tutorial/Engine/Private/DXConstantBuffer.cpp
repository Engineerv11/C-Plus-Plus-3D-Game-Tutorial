#include "GraphicsEngine.h"
#include "DXDeviceContext.h"
#include "DXConstantBuffer.h"

DXConstantBuffer::DXConstantBuffer()
{
}

DXConstantBuffer::~DXConstantBuffer()
{
}

bool DXConstantBuffer::Init(void* Buffer, UINT BufferSize)
{
    if (D3D11Buffer)D3D11Buffer->Release();

    D3D11_BUFFER_DESC buffer_desc;

    ZeroMemory(&buffer_desc, sizeof(buffer_desc));

    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.ByteWidth = BufferSize;
    buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data;

    ZeroMemory(&data, sizeof(data));

    data.pSysMem = Buffer;

    HRESULT result;

    result = GraphicsEngine::Instance()->D3D11Device->CreateBuffer(&buffer_desc, &data, &D3D11Buffer);

    if (FAILED(result))
    {
        return false;
    }

  
    

    return true;
}

bool DXConstantBuffer::Release()
{
    if (D3D11Buffer)D3D11Buffer->Release();
    delete this;

	return true;
}

void DXConstantBuffer::Update(DXDeviceContext* DeviceContext, void* Buffer)
{
    DeviceContext->D3D11DeviceContext->UpdateSubresource(D3D11Buffer, NULL, NULL, Buffer, NULL, NULL);
}
