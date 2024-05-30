#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	vertexBuffer->Release();
}

void VertexBuffer::SetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	Device::Get()->GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	Device::Get()->GetDC()->IASetPrimitiveTopology(type);
}
