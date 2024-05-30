#include "Framework.h"
#include "Monster_lv2.h"


Monster_lv2::Monster_lv2()
{
	type = MonsterType::LV2;

	senser = new ColliderRect({ 600, 400 });
	senser->SetParent(this);

	senserAttacker = new ColliderRect({ 300, 200 });
	senserAttacker->SetParent(this);

	body = new ColliderRect({ 30, 30 });
	body->SetParent(this);

	lScale *= 2.0f;

	AddAction();

	state = IDLE;
	curAction = actions[state];
	curAction->Play();

	stat_HP = 5.0f;

	movePower = 150.0f;
	moveSpeed = 0.0f;

	AttackCoolTimeMax = 4.0f;
	AttackCoolTime = AttackCoolTimeMax;
}

Monster_lv2::~Monster_lv2()
{
	delete senserAttacker;
}

void Monster_lv2::Update()
{
	if (!isPlay) return;

	Monster::Update();
	senserAttacker->Update();

	Gravity();


	if (stat_HP > 0) 
	{
		if (backMovingEvent) BackmovingEvent();
		else
		{
			if (!checkPlayer && !attacked) SetAction(IDLE);
			else if (attacked) Attack();
			else if (checkPlayer)
			{
				if (senserAttacker->Collision(OBJECT->GetPlayer()->GetCollider()) && moveCurrent >= movePower)
				{
					SetAction(State::ATTACK1);

					attacked = true;
				}
				else
				{
					SetAction(State::MOVE);
					Move();
				}
			}
		}
	}
}

void Monster_lv2::Render()
{
	if (!isPlay) return;

	Monster::Render();
	body->Render();
	senser->Render();
	senserAttacker->Render();
}

void Monster_lv2::Move()
{
	Vector2 LB = Vector2(body->L(), body->B());
	Vector2 RB = Vector2(body->R(), body->B());

	if (moveCurrent < movePower && !attacked)
	{
		moveCurrent += 75.0f * Time::Delta();
		moveSpeed = moveCurrent;
	}
	else if (attacked)
	{
		moveCurrent += 175.0f * Time::Delta();
		moveSpeed = moveCurrent;
	}

	for (Wall* wall : OBJECT->GetWall()->GetWalls())
	{
		if (!attacked) 
		{
			if (sensorRight) isRight = true;
			else isRight = false;

			if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::LEFT && !isRight)
			{
				moveCurrent = 0.0f;
				break;
			}
			else if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::RIGHT && isRight)
			{
				moveCurrent = 0.0f;
				break;
			}
		}
		else
		{
			if (!backMovingEvent)
			{
				if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::LEFT && !isRight)
				{
					backMovingEvent = true;
					break;
				}
				else if (wall->GetCollider()->Collision(body) && wall->GetType() == Wall::RIGHT && isRight)
				{
					backMovingEvent = true;
					break;
				}
			}
			else
			{
				moveCurrent = 0.0f;
			}
		}
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

void Monster_lv2::Gravity()
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

void Monster_lv2::Attack()
{
	Move();

	if (body->Collision(OBJECT->GetPlayer()->GetCollider()))
	{
		if (PlayerCheck())
			OBJECT->GetPlayer()->Damaged(1, true);
		else
			OBJECT->GetPlayer()->Damaged(1, false);
	}
}

void Monster_lv2::EndEvent()
{
	attacked = false;
	moveCurrent = 0.0f;
	moveSpeed = 0.0f;
	AttackCoolTime = 0.0f;
}

void Monster_lv2::BackmovingEvent()
{
	SetAction(State::MOVE);

	if (attacked) EndEvent();

	if (backMovingTime < 0.1f)
	{
		backMovingTime += Time::Delta();

		if (isRight)
		{
			lRotation.y = 0.0f;
			lTranslation += Vector2(-1, 0) * 300.0f * Time::Delta();
		}
		else
		{
			lRotation.y = XM_PI;
			lTranslation += Vector2(+1, 0) * 300.0f * Time::Delta();
		}
	}
	else
	{
		backMovingEvent = false;
		backMovingTime = 0.0f;
	}
}

void Monster_lv2::Damaged(float damaged)
{
	damagedTime = 0.2f;

	stat_HP -= damaged;

	if (stat_HP <= 0)
	{
		SetAction(DIE);
		moveCurrent = 0.0f;
		moveSpeed = 0.0f;
	}
}

void Monster_lv2::AddAction()
{
	actions.emplace(State::IDLE, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21));
	actions[State::IDLE]->SetPart(0, 3);
	
	actions.emplace(State::MOVE, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21));
	actions[State::MOVE]->SetPart(7, 10);
	
	actions.emplace(State::ATTACK1, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.1F));
	actions[State::ATTACK1]->SetPart(7, 10, false);
	actions[State::ATTACK1]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK2));
	
	actions.emplace(State::ATTACK2, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.09F));
	actions[State::ATTACK2]->SetPart(7, 10, false);
	actions[State::ATTACK2]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK3));
	
	actions.emplace(State::ATTACK3, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.08F));
	actions[State::ATTACK3]->SetPart(7, 10, false);
	actions[State::ATTACK3]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK4));
	
	actions.emplace(State::ATTACK4, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.07F));
	actions[State::ATTACK4]->SetPart(7, 10, false);
	actions[State::ATTACK4]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK5));
	
	actions.emplace(State::ATTACK5, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.06F));
	actions[State::ATTACK5]->SetPart(7, 10, false);
	actions[State::ATTACK5]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK6));
	
	actions.emplace(State::ATTACK6, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.05F));
	actions[State::ATTACK6]->SetPart(7, 10, false);
	actions[State::ATTACK6]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK7));
	
	actions.emplace(State::ATTACK7, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.04F));
	actions[State::ATTACK7]->SetPart(7, 10, false);
	actions[State::ATTACK7]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK8));
	
	actions.emplace(State::ATTACK8, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.03F));
	actions[State::ATTACK8]->SetPart(7, 10, false);
	actions[State::ATTACK8]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK9));
	
	actions.emplace(State::ATTACK9, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.02F));
	actions[State::ATTACK9]->SetPart(7, 10, false);
	actions[State::ATTACK9]->SetEndEvent(bind(&Monster_lv2::SetAction, this, ATTACK10));
	
	actions.emplace(State::ATTACK10, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21, 0.01F));
	actions[State::ATTACK10]->SetPart(7, 10, false);
	actions[State::ATTACK10]->SetEndEvent(bind(&Monster_lv2::EndEvent, this));

	actions.emplace(State::DIE, new Animation(L"Enemy/Fire/Monster_02.png", 7, 3, 21));
	actions[State::DIE]->SetPart(14, 20, false);
	actions[State::DIE]->SetEndEvent(bind(&Monster_lv2::IsPlayed, this, false));
}
