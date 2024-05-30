#include "Framework.h"
#include "Monster.h"


Monster::Monster()
{
}

Monster::~Monster()
{
	delete senser;
	delete body;
}

void Monster::Update()
{
	if (!isPlay) return;

	Character::Update();

	senser->Update();
	body->Update();

	PlayerCheck();

	damagedTime -= Time::Delta();

	 if (damagedTime > 0.1f)
	 	SetColor(1.0f, 0.0f, 0.0f, 1.0f - ((damagedTime - 0.1f) * 10.0f));
	 else if (damagedTime <= 0.1f && damagedTime > 0.0f)
	 {
	 	SetColor(1.0f, 0.0f, 0.0f, damagedTime * 10.0f);
	 }
	 else
	 	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Monster::Render()
{
	if (!isPlay) return;

	Character::Render();
}

bool Monster::PlayerCheck()
{
	if (senser->Collision(OBJECT->GetPlayer()->GetCollider()))
	{
		checkPlayer = true;

		if (senser->GlobalPosition().x < OBJECT->GetPlayer()->GlobalPosition().x)
		{
			sensorRight = true;
			lRotation.y = 0.0f;
		}
		else
		{
			sensorRight = false;
			lRotation.y = XM_PI;
		}
	}
	else checkPlayer = false;

	return sensorRight;
}

void Monster::SetAction(int state)
{
	if (this->state == state)
		return;

	this->state = (State)state;

	curAction = actions[state];
	curAction->Play();
}
