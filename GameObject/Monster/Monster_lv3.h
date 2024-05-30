#pragma once

class Monster_lv3 : public Monster
{
public:
	Monster_lv3();
	~Monster_lv3();

	void Update();
	void Render();

	void AddAction();

	void SpawnEvent();
	void SpawnEventEnd();

	void Attack();
	void Attack_First();
	void Attack_Second();

	void Die();

	virtual void Damaged(float damaged) override;

private:
	Collider* SpawnCollider;
	bool spawnCheck = false;

	vector<MonsterBullet*> bullets;
};