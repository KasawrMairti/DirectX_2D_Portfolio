#include "Framework.h"
#include "Monster_lv1.h"


Monster_lv1::Monster_lv1()
{
	type = MonsterType::LV1;

	senser = new ColliderRect({800, 400});
	senser->SetParent(this);

	body = new ColliderRect({20, 50});
	body->SetParent(this);

	for (UINT i = 0; i < 10; i++)
	{
		bullets.push_back(new Monster_lv1Attack());
	}
	
	AddAction();

	state = MOVE;
	curAction = actions[state];
	curAction->Play();

	movePower = 30.0f;
	moveSpeed = movePower;

	AttackCoolTimeMax = 2.5f;
	AttackCoolTime = AttackCoolTimeMax;
}

Monster_lv1::~Monster_lv1()
{
	for (Monster_lv1Attack* bullet : bullets)
		delete bullet;

	bullets.clear();
}

void Monster_lv1::Update()
{
	if (!isPlay) return;

	for (Monster_lv1Attack* bullet : bullets)
		bullet->Update();

	Monster::Update();
	Gravity();

	if (!checkPlayer) Move();
	else if (checkPlayer) Attack();
}

void Monster_lv1::Render()
{
	if (!isPlay) return;

	for (Monster_lv1Attack* bullet : bullets)
		bullet->Render();

	Monster::Render();
	body->Render();
	senser->Render();
}

void Monster_lv1::Move()
{
	SetAction(State::MOVE);

	Vector2 LB = Vector2(body->L(), body->B());
	Vector2 RB = Vector2(body->R(), body->B());


	for (Wall* wall : OBJECT->GetWall()->GetWalls())
	{
		if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::BOTTOM)
		{
			if (!wall->GetCollider()->Collision(LB))
			{
				isRight = true;
				break;
			}
			else if (!wall->GetCollider()->Collision(RB))
			{
				isRight = false;
				break;
			}
		}

		if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::LEFT)
			if (!isRight) isRight = true;
		else if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::RIGHT)
			if (isRight) isRight = false;
	}

	if (isRight)
	{
		lRotation.y = 0.0f;
		lTranslation += Vector2(+1, 0) * moveSpeed * Time::Delta();
	}
	else
	{
		lRotation.y = XM_PI;
		lTranslation += Vector2(-1, 0) * moveSpeed * Time::Delta();
	}

}

void Monster_lv1::Gravity()
{
	gravity += 980.0f * Time::Delta();

	for (Wall* wall : OBJECT->GetWall()->GetWalls())
	{
		if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::BOTTOM)
		{
			gravity = 0.0f;
			break;
		}
	}

	lTranslation += Vector2(0, -1) * gravity * Time::Delta();
}

void Monster_lv1::Attack()
{
	AttackCoolTime += Time::Delta();

	if (AttackCoolTime >= AttackCoolTimeMax)
	{
		AttackCoolTime = 0.0f;
		SetAction(ATTACK1);
	}
}

void Monster_lv1::AttackEvent()
{
	SetAction(ATTACK2);

	if (sensorRight) lRotation.y = 0.0f;
	else lRotation.y = XM_PI;

	for (Monster_lv1Attack* bullet : bullets)
	{
		if (!bullet->IsFire())
		{
			Vector2 dir = OBJECT->GetPlayer()->GlobalPosition() - this->GlobalPosition();
			bullet->Fire(lTranslation, dir.GetNormal(), 250.0f);
			break;
		}
	}
}

void Monster_lv1::Damaged(float damaged)
{
	damagedTime = 0.2f;

	stat_HP -= damaged;

	if (stat_HP <= 0)
	{
		SetAction(DIE);
		moveSpeed = 0.0f;
	}
}

void Monster_lv1::AddAction()
{
	actions.emplace(State::MOVE, new Animation(L"Enemy/Fire/Monster_01.png", 10, 4, 40));
	actions[State::MOVE]->SetPart(10, 13);

	actions.emplace(State::ATTACK1, new Animation(L"Enemy/Fire/Monster_01.png", 10, 4, 40));
	actions[State::ATTACK1]->SetPart(20, 26, false);
	actions[State::ATTACK1]->SetEndEvent(bind(&Monster_lv1::AttackEvent, this));

	actions.emplace(State::ATTACK2, new Animation(L"Enemy/Fire/Monster_01.png", 10, 4, 40));
	actions[State::ATTACK2]->SetPart(27, 29, false);
	actions[State::ATTACK2]->SetEndEvent(bind(&Monster_lv1::SetAction, this, IDLE));

	actions.emplace(State::IDLE, new Animation(L"Enemy/Fire/Monster_01.png", 10, 4, 40));
	actions[State::IDLE]->SetPart(0, 3);

	actions.emplace(State::DIE, new Animation(L"Enemy/Fire/Monster_01.png", 10, 4, 40));
	actions[State::DIE]->SetPart(30, 34, false);
	actions[State::DIE]->SetEndEvent(bind(&Monster_lv1::IsPlayed, this, false));
}