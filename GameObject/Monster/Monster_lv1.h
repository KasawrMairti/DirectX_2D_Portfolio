#pragma once

class Monster_lv1 : public Monster
{

public:
	Monster_lv1();
	~Monster_lv1();

	void Update();
	void Render();

	void Move();
	void Gravity();
	void Attack();
	void AttackEvent();
	
	virtual void Damaged(float damaged) override;

	void AddAction();

private:
	float gravity = 0.0f;

	vector<Monster_lv1Attack*> bullets;
};