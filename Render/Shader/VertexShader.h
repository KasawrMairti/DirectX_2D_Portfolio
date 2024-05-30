#pragma once

class VertexShader
{
public:
	VertexShader(wstring path);
	~VertexShader();
	
	void SetShader();

	void CreateInputLayout();

private:
	ID3D11InputLayout* inputLayout;

	ID3D11VertexShader* vertexShader;

	ID3DBlob* vertexBlob;

	ID3D11ShaderReflection* reflection = nullptr;
};
