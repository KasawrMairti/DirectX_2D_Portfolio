#include "Framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
	:data(data), dataSize(dataSize)
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = dataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	DEVICE->CreateBuffer(&desc, nullptr, &constantBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
	constantBuffer->Release();
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
	DC->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);
	DC->VSSetConstantBuffers(slot, 1, &constantBuffer);
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
	DC->UpdateSubresource(constantBuffer, 0, nullptr, data, 0, 0);
	DC->PSSetConstantBuffers(slot, 1, &constantBuffer);
}