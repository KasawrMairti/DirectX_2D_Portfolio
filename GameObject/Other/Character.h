#pragma once

class Character : public Transform
{
public:
	Character();
	Character(wstring file);
	virtual ~Character();

	virtual void Update();
	virtual void Render();

	void SetColor(float r, float g, float b, float a = 1.0f)
	{
		colorBuffer->SetData(r, g, b, a);
	}

	Vector4 GetColor() { return colorBuffer->GetColor(); }

protected:
	VertexShader* vertexShader = nullptr;
	 PixelShader*  pixelShader = nullptr;

	MatrixBuffer* worldBuffer = nullptr;
	 ColorBuffer* colorBuffer = nullptr;

	 map<int, Animation*> actions;
	 Animation* curAction = nullptr;

};
