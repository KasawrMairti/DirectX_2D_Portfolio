#include "Framework.h"
#include "Character.h"

Character::Character()
{
	vertexShader = new VertexShader(L"VertexTexture");
	 pixelShader = new  PixelShader(L"PixelTexture");

	 worldBuffer = new MatrixBuffer();
	 colorBuffer = new  ColorBuffer();
}

Character::Character(wstring file)
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new  PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer();
	colorBuffer = new  ColorBuffer();

	actions.emplace(0, new Animation(file, 1, 1));
	actions[0]->SetAll();

	curAction = actions[0];
	curAction->Play();
}

Character::~Character()
{
	delete vertexShader;
	delete  pixelShader;

	delete worldBuffer;
	delete colorBuffer;

	for (pair<int, Animation*> pair : actions)
		delete pair.second;

	actions.clear();
}

void Character::Update()
{
	if (curAction == nullptr)
		return;

	Transform::Update();
	curAction->Update();
}

void Character::Render()
{
	if (curAction == nullptr)
		return;

	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	colorBuffer->SetPSBuffer(0);

	vertexShader->SetShader();
	 pixelShader->SetShader();

	   curAction->Render();
}
