#pragma once

class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	~ConstantBuffer();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

private:
	ID3D11Buffer* constantBuffer;

	void* data;
	UINT  dataSize;
};
