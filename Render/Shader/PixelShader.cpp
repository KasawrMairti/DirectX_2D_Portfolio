#include "Framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring path)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    path = L"_Shader/" + path + L".hlsl";

    D3DCompileFromFile
    (
        path.c_str(),
        nullptr, nullptr,
        "PS", "ps_5_0",
        flags,
        0,
        &pixelBlob,
        nullptr
    );

    Device::Get()->GetDevice()->CreatePixelShader
    (
        pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(),
        nullptr,
        &pixelShader
    );
}

PixelShader::~PixelShader()
{
    pixelShader->Release();
      pixelBlob->Release();
}

void PixelShader::SetShader()
{
    Device::Get()->GetDC()->PSSetShader(pixelShader, nullptr, 0);
}
