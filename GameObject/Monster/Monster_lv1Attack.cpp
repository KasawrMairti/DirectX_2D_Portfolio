#include "Framework.h"
#include "Monster_lv1Attack.h"


Monster_lv1Attack::Monster_lv1Attack()
{
	actions.emplace(0, new Animation(L"EnemyWeapon/Fire/fire_danmaku.png", 5, 3, 15));
	actions[0]->SetPart(0, 3);

	actions.emplace(1, new Animation(L"EnemyWeapon/Fire/fire_danmaku.png", 5, 3, 15, 0.03f));
	actions[1]->SetPart(5, 14, false);
	actions[1]->SetEndEvent(bind(&Monster_lv1Attack::IsFired, this));

	curAction = actions[0];

	collider = new ColliderRect(curAction->GetSize() / 5);
	collider->SetParent(this);
}

Monster_lv1Attack::~Monster_lv1Attack()
{
	delete collider;
}

void Monster_lv1Attack::Update()
{
	if (!isFire) return;

	Character::Update();
	collider->Update();

	if (isDestroyed) return;

	lTranslation += dir * speed * Time::Delta();
	lRotation.z = atanf(dir.y / dir.x);

	if (dir.x < 0)
	{
		lRotation.x = 0.0f;
		lRotation.y = 0.0f;
	}
	else
	{
		lRotation.x = XM_PI;
		lRotation.y = XM_PI;
	}

	Hit();

	timelimit += Time::Delta();

	if (timelimit >= 10.0f)
	{
		SetAction(1);
		timelimit = 0.0f;
		isDestroyed = true;
	}

}

void Monster_lv1Attack::Render()
{
	if (!isFire) return;

	Character::Render();
}

void Monster_lv1Attack::Fire(Vector2 pos, Vector2 dir, float speed)
{
	isFire = true;
	isDestroyed = false;

	this->lTranslation = pos;
	this->dir = dir;
	this->speed = speed;

	SetAction(0);
	curAction->Play();	
}

void Monster_lv1Attack::Hit()
{
	if (collider->Collision(OBJECT->GetPlayer()->GetCollider()))
	{
		SetAction(1);
		isDestroyed = true;

		if (collider->GlobalPosition().x < OBJECT->GetPlayer()->GetCollider()->GlobalPosition().x)
			OBJECT->GetPlayer()->Damaged(1, true);
		else
			OBJECT->GetPlayer()->Damaged(1, false);
	}

	for (Wall* wall : OBJECT->GetWall()->GetWalls())
	{
		if (collider->Collision(wall->GetCollider()))
		{
			SetAction(1);
			isDestroyed = true;
		}
	}
}

void Monster_lv1Attack::SetAction(int state)
{
	if (this->state == state)
		return;

	this->state = state;

	curAction = actions[this->state];
	curAction->Play();
}
