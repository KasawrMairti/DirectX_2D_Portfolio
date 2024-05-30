#include "Framework.h"
#include "Effect.h"

Effect::Effect(wstring file, UINT frameX, UINT frameY, UINT nFrames, float updateTime)
{
	vertexShader = new VertexShader(L"VertexTexture");
	 pixelShader = new  PixelShader(L"PixelTexture");

	 worldBuffer = new MatrixBuffer();
	 colorBuffer = new  ColorBuffer();

	 curAction = new Animation(file, frameX, frameY, nFrames, updateTime);
	 curAction->SetAll(false);
	 curAction->SetEndEvent(bind(&Effect::Stop, this));

	 isActive = false;
}

Effect::~Effect()
{
	delete curAction;

	delete  worldBuffer;
	delete  colorBuffer;

	delete vertexShader;
	delete  pixelShader;
}

void Effect::Update()
{
	if (!isActive)
		return;

	curAction->Update();
	Transform::Update();
}

void Effect::Render()
{
	if (!isActive)
		return;

	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	colorBuffer->SetPSBuffer(0);

	vertexShader->SetShader();
	 pixelShader->SetShader();


	 switch (type)
	 {
	 case Effect::NORMAL:
		 curAction->Render();
		 break;
	 case Effect::ADDITIVE:
		 Environment::Get()->CreateAdditive();
		 curAction->Render();
		 Environment::Get()->CreateAlphaBlend();
		 break;
	 default:
		 break;
	 }
}

void Effect::Play(Vector2 position)
{
	isActive = true;

	lTranslation = position;

	curAction->Play();
}

void Effect::Stop()
{
	isActive = false;

	//curAction->Stop();
}
