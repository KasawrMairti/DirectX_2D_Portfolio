#pragma once

class Object : public Transform
{
public:
	Object(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Object(wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1));
	~Object();

	void Update();
	void Render();

	void SetColor(float r, float g, float b, float a) { colorBuffer->SetData(Vector4(r, g, b, a)); alpha = a; }

	Vector2 GetGlobalSize() { return Vector2(size.x * Scale().x, size.y * Scale().y); }

	bool& FadeInOut() { return fadeInOut; }

private:
	vector<VertexTexture> vertices;
	vector<UINT>		   indices;

	VertexBuffer* vertexBuffer;
	 IndexBuffer*  indexBuffer;

	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	 MatrixBuffer* worldBuffer;
	  ColorBuffer* colorBuffer;

	  Texture* texture;

	  Vector2 size;

	  float alpha = 1.0f;
	  bool fadeInOut = true;
};
