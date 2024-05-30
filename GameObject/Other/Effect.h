#pragma once

class Effect : public Transform
{
	enum Type
	{
		NORMAL,
		ADDITIVE
	} type = ADDITIVE;

public:
	Effect(wstring file, UINT frameX, UINT frameY, UINT nFrames = 0, float updateTime = 0.1f);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 position);
	void Stop();

private:
	VertexShader* vertexShader = nullptr;
	 PixelShader*  pixelShader = nullptr;

	MatrixBuffer* worldBuffer = nullptr;
	 ColorBuffer* colorBuffer = nullptr;

	Animation* curAction = nullptr;
};
