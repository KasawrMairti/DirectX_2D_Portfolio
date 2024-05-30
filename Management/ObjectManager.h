#pragma once

class ObjectManager : public Singleton<ObjectManager>
{
public:
	void SetPlayer(Player* player) { this->player = player; }
	Player* GetPlayer() { return player; }

	void SetWall(WallManager* wall) { this->wall = wall; }
	WallManager* GetWall() { return wall; }

	void SetMonster(MonsterManager* monster) { this->monster = monster; }
	MonsterManager* GetMonster() { return monster; }
	
	void SetBullet(PlayerBulletManager* bullet) { this->bullet = bullet; }
	PlayerBulletManager* GetBullet() { return bullet; }
	
private:
	Player* player;
	WallManager* wall;
	MonsterManager* monster;
	PlayerBulletManager* bullet;
};