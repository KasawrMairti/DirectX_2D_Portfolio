#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(vector<UINT>& indices)
{
	UINT count = indices.size();

	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = sizeof(UINT) * count;
	desc.Usage     = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = indices.data();

	DEVICE->CreateBuffer(&desc, &data, &indexBuffer);
}

IndexBuffer::~IndexBuffer()
{
	indexBuffer->Release();
}

void IndexBuffer::SetBuffer()
{
	DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
