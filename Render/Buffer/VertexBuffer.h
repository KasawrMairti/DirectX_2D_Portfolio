#pragma once

class VertexBuffer
{
public:
	template<typename T>
	VertexBuffer(vector<T>& vertices);
	~VertexBuffer();

    void SetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

private:
	ID3D11Buffer* vertexBuffer;

	UINT stride = 0;
	UINT offset = 0;
};

template<typename T>
inline VertexBuffer::VertexBuffer(vector<T>& vertices)
{
    D3D11_BUFFER_DESC bufferDesc = {};

    stride = sizeof(T);

    bufferDesc.ByteWidth = stride * vertices.size();
    bufferDesc.Usage     = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();

    Device::Get()->GetDevice()->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}
