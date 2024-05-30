#pragma once

class Polygons : public Transform
{
public:
	Polygons(Vector2 pos, float radius, UINT sectorCount = 36, Vector4 color = Vector4(1, 0, 0, 1));
	~Polygons();

	void Update();
	void Render();

private:
	vector<VertexColor> vertices;
	vector<UINT>		 indices;

	VertexBuffer* vertexBuffer;
	 IndexBuffer*  indexBuffer;

	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	MatrixBuffer*  worldBuffer;
};
