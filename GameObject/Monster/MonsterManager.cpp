#include "Framework.h"
#include "MonsterManager.h"


MonsterManager::MonsterManager()
{
	OBJECT->SetMonster(this);

	for (UINT i = 0; i < 20; i++)
	{
		Monster_lv1* monster1 = new Monster_lv1();
		monster1->Translation() = { -10000, -10000 };
		monster1->IsPlay() = false;
		monsters.push_back(monster1);

		Monster_lv2* monster2 = new Monster_lv2();
		monster2->Translation() = { -10000, -10000 };
		monster2->IsPlay() = false;
		monsters.push_back(monster2);
	}

	Monster_lv3* monster3 = new Monster_lv3();
	monster3->Translation() = { -10000, -10000 };
	monster3->IsPlay() = false;
	monsters.push_back(monster3);
}

MonsterManager::~MonsterManager()
{
	for (Monster* monster : monsters)
		delete monster;

	monsters.clear();
}

void MonsterManager::Update()
{
	for (Monster* monster : monsters)
		monster->Update();
}

void MonsterManager::Render()
{
	for (Monster* monster : monsters)
		monster->Render();
}

void MonsterManager::Add(MonsterType type, Vector2 Pos)
{
	for (Monster* monster : monsters)
	{
		if (!monster->IsPlay() && monster->Type() == type)
		{
			monster->Translation() = Pos;

			if (type == LV1)
			{
				monster->SetHP() = 2.0f;
				monster->SetAction(Monster::IDLE);
			}
			else if (type == LV2)
			{
				monster->SetHP() = 8.0f;
				monster->SetAction(Monster::MOVE);
			}
			else if (type == LV3) 
			{
				monster->SetHP() = 150.0f;
				monster->SetAction(Monster::NONE);
			}

			monster->IsPlay() = true;

			break;
		}
	}
}
