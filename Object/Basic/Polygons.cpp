#include "Framework.h"
#include "Polygons.h"

Polygons::Polygons(Vector2 pos, float radius, UINT sectorCount, Vector4 color)
{
	//Vertice
	vertices.push_back(VertexColor(pos, color));

	for (UINT i = 0; i < sectorCount; i++)
	{
		float angle = XM_2PI / sectorCount * i;

		Vector2 position =
		{
			cosf(angle) * radius,
			sinf(angle) * radius
		};

		vertices.push_back(VertexColor(pos + position, color));
	}

	//Indices
	for (UINT i = 0; i < sectorCount; i++)
	{
		indices.push_back(0);

		if (i == sectorCount - 1)
		{
			indices.push_back(1);
			indices.push_back(sectorCount);
			break;
		}

		indices.push_back(i + 2);
		indices.push_back(i + 1);
	}

	vertexBuffer = new VertexBuffer(vertices);
	 indexBuffer = new  IndexBuffer( indices);

	vertexShader = new VertexShader(L"VertexColor");
	 pixelShader = new  PixelShader( L"PixelColor");

	 worldBuffer = new MatrixBuffer();
}

Polygons::~Polygons()
{
	delete  worldBuffer;

	delete  pixelShader;
	delete vertexShader;

	delete  indexBuffer;
	delete vertexBuffer;
}

void Polygons::Update()
{
	Transform::Update();
}

void Polygons::Render()
{
	vertexBuffer->SetBuffer();
     indexBuffer->SetBuffer();
    vertexShader->SetShader();
     pixelShader->SetShader();

	 worldBuffer->SetData(world);
	 worldBuffer->SetVSBuffer(0);
    
    Device::Get()->GetDC()->DrawIndexed(indices.size(), 0, 0);
}
