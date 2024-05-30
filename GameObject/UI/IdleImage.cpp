#include "Framework.h"
#include "IdleImage.h"


IdleImage::IdleImage(wstring file, UINT frameX, UINT frameY)
{
	actions.emplace(0, new Animation(file, frameX, frameY));
	actions[0]->SetAll();

	curAction = actions[0];
	curAction->Play();
}

IdleImage::~IdleImage()
{
}

void IdleImage::Update()
{
	Character::Update();

	if (fadeInOut)
	{
		if (alpha < 1.0f)
		{
			alpha += 0.2f * Time::Delta();
			this->SetColor(this->GetColor().x, this->GetColor().y, this->GetColor().z, alpha);
		}
	}
	else if (!fadeInOut)
	{
		if (alpha > 0.0f)
		{
			alpha -= 0.2f * Time::Delta();
			this->SetColor(this->GetColor().x, this->GetColor().y, this->GetColor().z, alpha);
		}
	}
}

void IdleImage::Render()
{
	Character::Render();
}
