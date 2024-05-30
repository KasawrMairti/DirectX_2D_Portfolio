#pragma once

class PixelShader
{
public:
	PixelShader(wstring path);
	~PixelShader();

	void SetShader();

private:
	ID3D11PixelShader* pixelShader;

	ID3DBlob* pixelBlob;
};
