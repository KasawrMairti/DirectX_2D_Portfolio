#include "Framework.h"
#include "PlayerBullet.h"



PlayerBullet::PlayerBullet(WeaponType type, bool isMove)
	:weapontype(type), isMove(isMove)
{
	if (!isMove)
	{
		isFire = true;
		this->type = DESTROY;
	}
	else this->type = RIGHT;

	selector = new Character(L"UI/WhiteBox.png");
	selector->SetColor(0.4f, 1.0f, 0.4f, 0.6f);
	selector->Scale() *= 0.9f;
	selector->SetParent(this);

	if (type == PlayerBullet::NORMAL)
	{
		collider = new ColliderRect({10.0f, 10.0f});
		collider->Translation().y -= 5.0f;
		actions.emplace(StateType::RIGHT, new Animation(L"PlayerWeapon/Weapon_earth.png", 5, 2));
		actions.emplace(StateType::DESTROY, new Animation(L"PlayerWeapon/Weapon_earth.png", 5, 2));
		actions[StateType::RIGHT]->SetPart(0, 3);
		actions[StateType::DESTROY]->SetPart(5, 8, false);
		actions[StateType::DESTROY]->SetEndEvent(bind(&PlayerBullet::EndEvent, this));

		selector->Translation().y -= 6.0f;
	}
	else if (type == PlayerBullet::FIRE)
	{
		collider = new ColliderRect({70.0f, 50.0f});
		collider->Translation().x += 35.0f;
		collider->Translation().y += 5.0f;
		actions.emplace(StateType::RIGHT, new Animation(L"PlayerWeapon/Weapon_Fire.png", 6, 3));
		actions.emplace(StateType::UP, new Animation(L"PlayerWeapon/Weapon_Fire.png", 6, 3));
		actions.emplace(StateType::DOWN, new Animation(L"PlayerWeapon/Weapon_Fire.png", 6, 3));
		if (isMove)
		{
			actions[StateType::RIGHT]->SetPart(0, 4, false);
			actions[StateType::RIGHT]->SetEndEvent(bind(&PlayerBullet::EndEvent, this));
		}
		else
			actions[StateType::RIGHT]->SetPart(0, 4);
		actions[StateType::UP]->SetPart(6, 10, false);
		actions[StateType::DOWN]->SetPart(12, 16, false);
		actions[StateType::UP]->SetEndEvent(bind(&PlayerBullet::EndEvent, this));
		actions[StateType::DOWN]->SetEndEvent(bind(&PlayerBullet::EndEvent, this));

		selector->Translation().x += 30.0f;
		selector->Translation().y -= 6.0f;
	}
	else if (type == PlayerBullet::ICE)
	{
		collider = new ColliderRect({16.0f, 16.0f});
		actions.emplace(StateType::RIGHT, new Animation(L"PlayerWeapon/Weapon_Ice.png", 5, 2));
		actions.emplace(StateType::DESTROY, new Animation(L"PlayerWeapon/Weapon_Ice.png", 5, 2));
		actions[StateType::RIGHT]->SetPart(0, 3);
		actions[StateType::DESTROY]->SetPart(5, 8, false);
		actions[StateType::DESTROY]->SetEndEvent(bind(&PlayerBullet::EndEvent, this));

		selector->Translation().y -= 6.0f;
	}
	else if (type == PlayerBullet::THURNDER)
	{
		collider = new ColliderRect({18.0f, 18.0f});
		colliderDamage = new ColliderRect({80.0f, 80.0f});
		collider->Translation().y -= 8.0f;
		colliderDamage->Translation().y -= 8.0f;
		actions.emplace(StateType::RIGHT, new Animation(L"PlayerWeapon/Weapon_Thunder.png", 4, 1, 4));
		actions.emplace(StateType::DESTROY, new Animation(L"PlayerWeapon/Weapon_ThunderDestroy.png", 6, 1, 6));
		actions[StateType::RIGHT]->SetPart(0, 3);
		actions[StateType::DESTROY]->SetPart(0, 5, false);
		actions[StateType::DESTROY]->SetEndEvent(bind(&PlayerBullet::EndEvent, this));

		selector->Translation().y -= 15.0f;
	}

	curAction = actions[StateType::RIGHT];

	collider->SetParent(this);
	if (colliderDamage != nullptr) colliderDamage->SetParent(this);
}

PlayerBullet::~PlayerBullet()
{
	delete collider;
	if (colliderDamage != nullptr) delete colliderDamage;
	delete selector;
}

void PlayerBullet::Update()
{
	if (!isFire) return;

	Character::Update();

	collider->Update();
	if (colliderDamage != nullptr) colliderDamage->Update();

	if (type == RIGHT)
	{
		limitTime += Time::Delta();
		fireCooltime += Time::Delta();
	
		switch (weapontype)
		{
		case PlayerBullet::NORMAL:
		{
			lTranslation += dir * speed * Time::Delta();
	
			for (Monster* monster : OBJECT->GetMonster()->Monsters())
			{
				if (collider->Collision(monster->GetBody()) && monster->IsPlay())
				{
					monster->Damaged(2.0f);
	
					type = DESTROY;
					curAction = actions[DESTROY];
					curAction->Play();
	
					break;
				}
			}

			for (Wall* wall : OBJECT->GetWall()->GetWalls())
			{
				if (collider->Collision(wall->GetCollider()))
				{
					type = DESTROY;
					curAction = actions[DESTROY];
					curAction->Play();

					break;
				}
			}
		}
		break;
		case PlayerBullet::FIRE:
		{
			lTranslation = OBJECT->GetPlayer()->Translation();
			lTranslation.y += 15.0f;
			
			if (OBJECT->GetPlayer()->IsRight())
			{
				lTranslation.x += 10.0f;
				lRotation.y = 0.0f;
			}
			else
			{
				lTranslation.x -= 10.0f;
				lRotation.y = XM_PI;
			}

			if (fireCooltime >= 0.1f)
			{
				for (Monster* monster : OBJECT->GetMonster()->Monsters())
				{
					if (collider->Collision(monster->GetBody()) && monster->IsPlay())
					{
						monster->Damaged(1.0f);
					}
				}
	
				fireCooltime = 0.0f;
			}
		}
		break;
		case PlayerBullet::ICE:
		{
			lTranslation += dir * speed * Time::Delta();
	
			for (Monster* monster : OBJECT->GetMonster()->Monsters())
			{
				if (collider->Collision(monster->GetBody()) && monster->IsPlay())
				{
					monster->Damaged(1.0f);
	
					type = DESTROY;
					curAction = actions[DESTROY];
					curAction->Play();
	
					break;
				}
			}

			for (Wall* wall : OBJECT->GetWall()->GetWalls())
			{
				if (collider->Collision(wall->GetCollider()))
				{
					type = DESTROY;
					curAction = actions[DESTROY];
					curAction->Play();

					break;
				}
			}
		}
		break;
		case PlayerBullet::THURNDER:
		{
			lTranslation += dir * speed * Time::Delta();
	
			bool damageCheck = false;

			for (Wall* wall : OBJECT->GetWall()->GetWalls())
			{
				if (collider->Collision(wall->GetCollider()) && !damageCheck)
				{
					damageCheck = true;
					break;
				}
			}

			for (Monster* monster : OBJECT->GetMonster()->Monsters())
			{
				if (collider->Collision(monster->GetBody()) && monster->IsPlay() && !damageCheck)
				{
					damageCheck = true;
					break;
				}
			}
	
			if (damageCheck) 
			{
				for (Monster* monster : OBJECT->GetMonster()->Monsters())
				{
					if (colliderDamage->Collision(monster->GetBody()) && monster->IsPlay()
						&& damageCheck)
					{
						monster->Damaged(1.0f);
					}
				}

				type = DESTROY;
				curAction = actions[DESTROY];
				curAction->Play();
			}
		}
		break;
		default:
			break;
		}

		if (limitTime >= 10.0f)
		{
			type = DESTROY;
			curAction = actions[DESTROY];
			curAction->Play();
			limitTime = 0.0f;
		}
	}

	if (isSelect)
	{
		selector->Update();

		invisibleTimer += 0.5f * Time::Delta();

		// 알파값이 1.0 되고 0 되게 타이머로 반복
		if (invisibleTimer <= 0.2f)
			selector->SetColor(0.4f, 1.0f, 0.4f, invisibleTimer * 2.0f);
		else if (invisibleTimer <= 0.4f && invisibleTimer > 0.2f)
			selector->SetColor(0.4f, 1.0f, 0.4f, (0.4f - invisibleTimer) * 2.0f);
		else
			invisibleTimer = 0.0f;
	}
}

void PlayerBullet::Render()
{
	if (!isFire) return;

	Character::Render();

	collider->Render();
	if (colliderDamage != nullptr) colliderDamage->Render();

	if (isSelect) selector->Render();
}

void PlayerBullet::EndEvent()
{
	isFire = false;
	type = DESTROY;
}

void PlayerBullet::Fire(Vector2 pos, Vector2 dir, float speed)
{
	this->lTranslation = pos;
	this->dir = dir;
	this->speed = speed;
	limitTime = 0.0f;

	type = RIGHT;
	curAction = actions[RIGHT];
	curAction->Play();

	isFire = true;
}
