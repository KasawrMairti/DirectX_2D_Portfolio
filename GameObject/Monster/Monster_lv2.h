#pragma once

class Monster_lv2 : public Monster
{
public:
	Monster_lv2();
	~Monster_lv2();

	void Update();
	void Render();

	void Move();
	void Gravity();
	void Attack();
	void EndEvent();
	void BackmovingEvent();

	virtual void Damaged(float damaged) override;

	void AddAction();

private:
	Collider* senserAttacker = nullptr;

	float gravity = 0.0f;
	float moveCurrent = 0.0f;
	bool attacked = false;

	bool backMovingEvent = false;
	float backMovingTime = 0.0f;
};