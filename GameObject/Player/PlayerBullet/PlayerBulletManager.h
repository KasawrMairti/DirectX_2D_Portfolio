#pragma once

class PlayerBulletManager
{
public:
	PlayerBulletManager();
	~PlayerBulletManager();

	void Update();
	void Render();

	void Fire(Vector2 pos, Vector2 dir, float speed, PlayerBullet::WeaponType type);

private:
	vector<PlayerBullet*> bullets;
};