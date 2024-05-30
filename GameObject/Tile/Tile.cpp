#include "Framework.h"
#include "Tile.h"


Tile::Tile(wstring file, Vector2 pos, Vector2 tileSize, Vector2 tileTranslation)
	:pos(pos)
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new  PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer;
	colorBuffer = new  ColorBuffer;

	tile = new Frame(file);

	lTranslation = pos;
}

Tile::~Tile()
{
	delete vertexShader;
	delete  pixelShader;

	delete worldBuffer;
	delete colorBuffer;

	delete tile;
}

void Tile::Update()
{
	Transform::Update();
}

void Tile::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	colorBuffer->SetPSBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();

	tile->Render();
}
