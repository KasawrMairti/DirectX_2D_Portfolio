#pragma once

class Tile : public Transform
{
public:
	Tile(wstring file, Vector2 pos, Vector2 tileSize = { 0, 0 }, Vector2 tileTranslation = { 0, 0 });
	~Tile();

	void Update();
	void Render();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	Frame* tile;
	Vector2 pos;
};