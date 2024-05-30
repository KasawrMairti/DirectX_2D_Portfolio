#include "Framework.h"
#include "PlayerBulletManager.h"


PlayerBulletManager::PlayerBulletManager()
{
	OBJECT->SetBullet(this);

	for (UINT i = 0; i < 20; i++)
	{
		bullets.push_back(new PlayerBullet(PlayerBullet::NORMAL));
		bullets.push_back(new PlayerBullet(PlayerBullet::FIRE));
		bullets.push_back(new PlayerBullet(PlayerBullet::ICE));
		bullets.push_back(new PlayerBullet(PlayerBullet::THURNDER));
	}
}

PlayerBulletManager::~PlayerBulletManager()
{
	for (PlayerBullet* bullet : bullets)
		delete bullet;

	bullets.clear();
}

void PlayerBulletManager::Update()
{
	for (PlayerBullet* bullet : bullets)
		bullet->Update();
}

void PlayerBulletManager::Render()
{
	for (PlayerBullet* bullet : bullets)
		bullet->Render();
}

void PlayerBulletManager::Fire(Vector2 pos, Vector2 dir, float speed, PlayerBullet::WeaponType type)
{
	for (PlayerBullet* bullet : bullets)
	{
		if (bullet->Type() == type && !bullet->IsFire())
		{
			bullet->Fire(pos, dir, speed);
			break;
		}
	}
}

