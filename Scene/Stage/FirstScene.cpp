#include "Framework.h"
#include "FirstScene.h"


FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{
}

void FirstScene::Update()
{
	if (timeAfter >= 5.0f && !loading) ObjectPosition();
	else timeAfter += Time::Delta();

	if (!loading) return;

	for (Object* background : backgrounds)
		background->Update();

	monster->Update();
	player->Update();
	tile->Update();
	wall->Update();

	UI->Update();
}

void FirstScene::Render()
{
	if (!loading) return;

	for (Object* background : backgrounds)
		background->Render();

	monster->Render();
	player->Render();
	tile->Render();
	wall->Render();

	UI->Render();
}

void FirstScene::Initialize()
{
	player = new Player();
	player->Translation() = { 200, 100 };

	CAMERA->SetTarget(player, 1.0f);
	CAMERA->SetTranslation(player);
	CAMERA->TargetMode();

	MakeBG();
	MakeTile();
	MakeWall();
	MakeMonster();
}

void FirstScene::Release()
{
	delete player;
	delete monster;
	delete tile;
	delete wall;

	for (Object* background : backgrounds)
		delete background;

	backgrounds.clear();
}

void FirstScene::MakeBG()
{
	int backCount = 2;
	for (UINT i = 0; i < backCount; i++)
	{
		backgrounds.push_back(new Object(L"Background/fire_bg_01.png"));
		backgrounds[i]->SetColor(0.5f, 0.5f, 0.5f, 1.0f);
		backgrounds[i]->Scale() *= 2.0f;
		backgrounds[i]->Translation().x = 1280.0f;
		backgrounds[i]->Translation().y = 325.0f;
		backgrounds[i]->Translation().x += backgrounds[i]->GetGlobalSize().x * i;
	}

	float L = backgrounds[0]->Translation().x - backgrounds[0]->GetGlobalSize().x * 0.5f;
	float B = backgrounds[0]->Translation().y - backgrounds[0]->GetGlobalSize().y * 0.5f;

	float R = 1760.0f;
	float T = backgrounds[backCount - 1]->Translation().y + backgrounds[backCount - 1]->GetGlobalSize().y * 0.5f;

	CAMERA->Areas() = { {L, R, T, B}, {1760.0f, 3000.0f, T, B} };
}

void FirstScene::MakeTile()
{
	tile = new TileManager();

	// 마그마
	for (int i = 0; i < 3; i++)
	{
		float x = i * 64.0f + 550.0f;

		tile->AddTile(L"Tile/magma_2.png", { x, -20.0f });
		tile->AddTile(L"Tile/magma_5.png", { x, -70.0f });
	}

	// 마그마2
	for (int i = 0; i < 25; i++)
	{
		float x = i * 64.0f + 1600.0f;

		tile->AddTile(L"Tile/magma_2.png", { x, -20.0f });
		tile->AddTile(L"Tile/magma_5.png", { x, -70.0f });
	}

	// 상단 ─
	for (int i = 0; i < 60; i++)
	{
		float x = i * 44.0f + 124.0f;
	
		tile->AddTile(L"Tile/Tile_magma_2.png", { x, 594.7f + 88.0f });
	}
	
	// ┌
	tile->AddTile(L"Tile/Tile_magma_1.png", { 81.35f, 590.7f + 88.0f });
	
	// │
	for (int i = 0; i < 14; i++)
	{
		float y = i * 44.2f + 63.5f;
	
		tile->AddTile(L"Tile/Tile_magma_4.png", { 77.0f, y });
	}
	
	// └
	tile->AddTile(L"Tile/Tile_magma_6.png", { 81.35f, 21.0f });


	// 좌측 벽 채우기
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			float x = i * 42.0f + 0.0f;
			float y = j * 42.0f - 10.0f;

			tile->AddTile(L"Tile/Tile_magma_9.png", { x, y });
		}
	}

	// 하단 ─
	for (int i = 0; i < 10; i++)
	{
		float x = i * 44.0f + 124.0f;
	
		tile->AddTile(L"Tile/Tile_magma_7.png", { x, 17.0f });
	}

	// 하단 벽 채우기
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			float x = i * 42.0f + 59.0f;
			float y = j * 42.0f - 21.0f;

			tile->AddTile(L"Tile/Tile_magma_9.png", { x, y });
		}
	}
	////
	tile->AddTile(L"Tile/Tile_magma_6.png", { 695.0f, 21.0f });	 
	tile->AddTile(L"Tile/Tile_magma_4.png", { 690.0f, 60.0f });	 
	
	// 2구역
	// 하단 ─
	for (int i = 0; i < 20; i++)
	{
		float x = i * 44.0f + 738.0f;
	
		tile->AddTile(L"Tile/Tile_magma_7.png", { x, 17.0f });
	}

	// 하단 벽 채우기
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			float x = i * 42.0f + 695.0f;
			float y = j * 42.0f - 21.0f;

			tile->AddTile(L"Tile/Tile_magma_9.png", { x, y });
		}
	}

	tile->AddTile(L"Tile/Tile_magma_8.png", { 1577.0f, 21.0f });
	tile->AddTile(L"Tile/Tile_magma_5.png", { 1581.0f, 60.0f });	 
	////

	// 다음 장소 3구역
	// 하단 ─
	for (int i = 0; i < 17; i++)
	{
		float x = i * 44.0f + 1718.0f;

		tile->AddTile(L"Tile/Tile_magma_7.png", { x, 17.0f });
	}

}

void FirstScene::MakeWall()
{
	wall = new WallManager();

	wall->AddWall({30.0f, 650.0f}, {77.0f, 350.0f}, Wall::LEFT);
	wall->AddWall({1500.0f, 5.0f}, {820.0f, 670.0f}, Wall::TOP);
	wall->AddWall({500.0f, 5.0f}, {288.0f, 30.0f}, Wall::BOTTOM);
	wall->AddWall({5.0f, 100.0f}, {537.0f, -20.0f}, Wall::LEFT);

	// 2구역
	wall->AddWall({5.0f, 160.0f}, {675.0f, 0.0f}, Wall::RIGHT);
	wall->AddWall({28.0f, 5.0f}, {688.0f, 80.0f}, Wall::BOTTOM);
	wall->AddWall({5.0f, 60.0f}, {700.0f, 50.0f}, Wall::LEFT);
	wall->AddWall({865.0f, 5.0f}, {1135.0f, 30.0f}, Wall::BOTTOM);
	wall->AddWall({5.0f, 60.0f}, {1570.0f, 50.0f}, Wall::RIGHT);
	wall->AddWall({28.0f, 5.0f}, {1583.0f, 80.0f}, Wall::BOTTOM);
	wall->AddWall({5.0f, 160.0f}, {1595.0f, 0.0f}, Wall::LEFT);

	// 3구역
	wall->AddWall({ 880.0f, 5.0f }, { 2135.0f, 28.0f }, Wall::BOTTOM);
}

void FirstScene::MakeMonster()
{
	monster = new MonsterManager();
	
	monster->Add(MonsterManager::LV1, { 800, 55 });
	monster->Add(MonsterManager::LV1, { 900, 55 });
	monster->Add(MonsterManager::LV1, { 1000, 55 });

	monster->Add(MonsterManager::LV2, { 400, 90 });
	monster->Add(MonsterManager::LV2, { 1200, 90 });

	monster->Add(MonsterManager::LV3, { 2700, 360 });
}

void FirstScene::ObjectPosition()
{
	player->Translation() = { 200, 100 };

	loading = true;
}
