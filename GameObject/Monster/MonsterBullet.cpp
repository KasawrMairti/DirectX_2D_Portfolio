#include "Framework.h"
#include "MonsterBullet.h"


MonsterBullet::MonsterBullet()
{
	isFire = false;
	originalScale = lScale;

	AddAction();

	collider = new ColliderRect({ 15.0f, 30.0f });
	collider->SetParent(this);
}

MonsterBullet::~MonsterBullet()
{
	delete collider;
}

void MonsterBullet::Update()
{
	if (!isFire) return;

	Character::Update();
	collider->Update();

	if (!stopping)
	{
		Move();
		Hit();
	}

	limitTime += Time::Delta();
	if (limitTime >= 5.0f) isFire = false;
}

void MonsterBullet::Render()
{
	if (!isFire) return;

	Character::Render();
	collider->Render();
}

void MonsterBullet::Move()
{
	lTranslation += dir * speed * Time::Delta();

	gravity += 980.0f * Time::Delta();

	lTranslation += Vector2(0, -1) * gravity * Time::Delta();
}

void MonsterBullet::Hit()
{
	if (collider->Collision(OBJECT->GetPlayer()->GetCollider()))
	{
		if (collider->GlobalPosition().x < OBJECT->GetPlayer()->GetCollider()->GlobalPosition().x)
			OBJECT->GetPlayer()->Damaged(1, true);
		else
			OBJECT->GetPlayer()->Damaged(1, false);
	}

	for (Wall* wall : OBJECT->GetWall()->GetWalls())
	{
		if (collider->Collision(wall->GetCollider()) && wall->GetType() == Wall::BOTTOM
			&& !stopping)
		{
			SetAction(1);
			lScale *= 2.0f;
			speed = 0.0f;
			gravity = 0.0f;
			stopping = true;

			break;
		}
	}
}

void MonsterBullet::EndEvent()
{
	limitTime = 0;
	lScale = originalScale;

	isFire = false;
	SetAction(0);
}

void MonsterBullet::AddAction()
{
	actions.emplace(0, new Animation(L"EnemyWeapon/Fire/magma_raku.png", 4, 1, 4));
	actions[0]->SetPart(0, 3);

	actions.emplace(1, new Animation(L"EnemyWeapon/Fire/magma_shot.png", 4, 1, 4));
	actions[1]->SetPart(0, 3, false);
	actions[1]->SetEndEvent(bind(&MonsterBullet::EndEvent, this));
}

void MonsterBullet::SetAction(int state)
{
	if (this->state == state)
		return;

	this->state = state;

	curAction = actions[this->state];
	curAction->Play();
}

void MonsterBullet::Fire(Vector2 pos, Vector2 dir, float speed)
{
	this->lTranslation = pos;
	this->dir = dir;
	this->speed = speed;
	limitTime = 0.0f;
	gravity = 0.0f;

	state = 0;
	curAction = actions[0];
	curAction->Play();

	stopping = false;

	isFire = true;
}
