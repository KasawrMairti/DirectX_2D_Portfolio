#pragma once

class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

public:
	void CreateAdditive();
	void CreateAlphaBlend();

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateRasterizeState();

private:
	MatrixBuffer* pBuffer;

	ID3D11SamplerState* samplerState;

	ID3D11BlendState* alphaBlendState;

	ID3D11RasterizerState* rasterizerState;
};
