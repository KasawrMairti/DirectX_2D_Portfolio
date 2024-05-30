#include "Framework.h"
#include "Monster_lv3.h"


Monster_lv3::Monster_lv3()
{
	type = MonsterType::LV3;

	lScale *= 2.5f;

	senser = new ColliderRect({ 0, 0 });
	senser->SetParent(this);

	body = new ColliderRect({ 200.0f, 200.0f });
	body->SetParent(this);
	body->Translation().y -= 50.0f;

	SpawnCollider = new ColliderRect({5.0f, 1000.0f});
	SpawnCollider->SetParent(this);
	SpawnCollider->Translation().x -= 250.0f;

	for (UINT i = 0; i < 25; i++)
	{
		MonsterBullet* bullet = new MonsterBullet();
		bullets.push_back(bullet);
	}

	AddAction();

	state = NONE;
	curAction = actions[NONE];

	stat_HP = 100.0f;

	movePower = 0.0f;
	moveSpeed = 0.0f;

	AttackCoolTimeMax = 3.0f;
	AttackCoolTime = AttackCoolTimeMax;
}

Monster_lv3::~Monster_lv3()
{
	delete SpawnCollider;

	for (MonsterBullet* bullet : bullets)
		delete bullet;

	bullets.clear();
}

void Monster_lv3::Update()
{
	if (!isPlay) return;

	Monster::Update();

	for (MonsterBullet* bullet : bullets)
		bullet->Update();

	if (!spawnCheck)
	{
		SpawnCollider->Update();
		SpawnEvent();
	}
	else
	{
		AttackCoolTime += Time::Delta();

		if (AttackCoolTime >= AttackCoolTimeMax)
		{
			Attack();
		}
	}
}

void Monster_lv3::Render()
{
	if (!isPlay) return;

	Monster::Render();

	for (MonsterBullet* bullet : bullets)
		bullet->Render();

	body->Render();
	if (!spawnCheck) SpawnCollider->Render();
}

void Monster_lv3::SpawnEvent()
{
	if (SpawnCollider->Collision(OBJECT->GetPlayer()->GetCollider()))
	{
		SetAction(SPAWN);
	}
}

void Monster_lv3::SpawnEventEnd()
{
	spawnCheck = true;
	SetAction(IDLE);
}

void Monster_lv3::Attack()
{
	AttackCoolTime = 0.0f;

	int randomAttack = rand() % 100;

	if (randomAttack < 50) SetAction(State::ATTACK1);
	else SetAction(State::ATTACK2);
}

void Monster_lv3::Attack_First()
{
	SetAction(State::ATTACK3);
		
	for (int i = 0; i < 12; i++)
	{
		for (MonsterBullet* bullet : bullets)
		{
			if (!bullet->IsFire())
			{
				Vector2 attackPos = lTranslation + Vector2(-380.0f, -300.0f);
				Vector2 dirPos = attackPos + Vector2((float)(rand() % 200) - 170, +500.0f);
				Vector2 dir = dirPos - attackPos;
				bullet->Fire(attackPos, dir.GetNormal(), 1000.0f);

				break;
			}
		}
	}
}

void Monster_lv3::Attack_Second()
{
	SetAction(State::IDLE);

	OBJECT->GetMonster()->Add(MonsterManager::LV1, { (float)(2000 + rand() % 500), 600 });
	OBJECT->GetMonster()->Add(MonsterManager::LV1, { (float)(2000 + rand() % 500), 600 });
	OBJECT->GetMonster()->Add(MonsterManager::LV2, { (float)(2000 + rand() % 500), 600 });
}

void Monster_lv3::Die()
{
	isPlay = false;
}

void Monster_lv3::Damaged(float damaged)
{
	damagedTime = 0.2f;

	stat_HP -= damaged;

	if (stat_HP <= 0)
	{
		SetAction(DIE);
	}
}

void Monster_lv3::AddAction()
{
	actions.emplace(State::IDLE, new Animation(L"Enemy/Fire/monster_titan_iwa_mag.png", 8, 5, 40));
	actions[State::IDLE]->SetPart(0, 3);

	actions.emplace(State::SPAWN, new Animation(L"Enemy/Fire/monster_titan_iwa_mag.png", 8, 5, 40));
	actions[State::SPAWN]->SetPart(8, 15, false);
	actions[State::SPAWN]->SetEndEvent(bind(&Monster_lv3::SpawnEventEnd, this));
	
	actions.emplace(State::ATTACK1, new Animation(L"Enemy/Fire/monster_titan_iwa_mag.png", 8, 5, 40));
	actions[State::ATTACK1]->SetPart(16, 20, false);
	actions[State::ATTACK1]->SetEndEvent(bind(&Monster_lv3::Attack_First, this));
	
	actions.emplace(State::ATTACK3, new Animation(L"Enemy/Fire/monster_titan_iwa_mag.png", 8, 5, 40));
	actions[State::ATTACK3]->SetPart(20, 22, false);
	actions[State::ATTACK3]->SetEndEvent(bind(&Monster_lv3::SetAction, this, IDLE));
	
	actions.emplace(State::ATTACK2, new Animation(L"Enemy/Fire/monster_titan_iwa_mag.png", 8, 5, 40));
	actions[State::ATTACK2]->SetPart(24, 29, false);
	actions[State::ATTACK2]->SetEndEvent(bind(&Monster_lv3::Attack_Second, this));
	
	actions.emplace(State::DIE, new Animation(L"Enemy/Fire/monster_titan_iwa_mag.png", 8, 5, 40));
	actions[State::DIE]->SetPart(32, 36, false);
	actions[State::DIE]->SetEndEvent(bind(&Monster_lv3::Die, this));

	actions.emplace(State::NONE, new Animation(L"UI/invisible.png", 1, 1));
	actions[State::NONE]->SetPart(0, 0);
}