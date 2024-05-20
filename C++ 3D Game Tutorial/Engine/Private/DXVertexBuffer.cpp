#include "GraphicsEngine.h"
#include "DXVertexBuffer.h"

DXVertexBuffer::DXVertexBuffer():Buffer(nullptr),InputLayout(nullptr)
{
}

DXVertexBuffer::~DXVertexBuffer()
{
}

bool DXVertexBuffer::Init(void* Vertices, UINT InVertexSize, UINT InVertexCount, void* ShaderBytecode, UINT BytecodeLength)
{
    if (Buffer)Buffer->Release();
    if (InputLayout)InputLayout->Release();

    VertexSize = InVertexSize;
    VertexCount = InVertexCount;

    D3D11_BUFFER_DESC buffer_desc;

    ZeroMemory(&buffer_desc, sizeof(buffer_desc));

    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.ByteWidth = VertexCount * VertexSize;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data;

    ZeroMemory(&data, sizeof(data));

    data.pSysMem = Vertices;

    HRESULT result;

    result = GraphicsEngine::Instance()->D3D11Device->CreateBuffer(&buffer_desc, &data, &Buffer);

    if (FAILED(result))
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC input_layout[] =
    {
        // LPCSTR SemanticName;     语义名称
        // UINT SemanticIndex;      语义索引
        // DXGI_FORMAT Format;      格式
        // UINT InputSlot;          输入插槽
        // UINT AlignedByteOffset;  对齐字节偏移
        // D3D11_INPUT_CLASSIFICATION InputSlotClass;   输入插槽类型
        // UINT InstanceDataStepRate;                   实例数据步长

        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    UINT input_layout_size = ARRAYSIZE(input_layout);

    result = GraphicsEngine::Instance()->D3D11Device->CreateInputLayout(input_layout, input_layout_size,ShaderBytecode,BytecodeLength,&InputLayout);

    if (FAILED(result))
    {
        return false;
    }

    return true;
}

bool DXVertexBuffer::Release()
{
    InputLayout->Release();
    Buffer->Release();
    delete this;

    return true;
}

UINT DXVertexBuffer::GetVertexCount()
{
    return VertexCount;
}
