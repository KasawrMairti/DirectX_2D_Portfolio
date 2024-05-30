#pragma once

class PlayerBullet : public Character
{
public:
	enum WeaponType
	{
		NORMAL,
		FIRE,
		ICE,
		THURNDER
	};

	enum StateType
	{
		RIGHT,
		UP,
		DOWN,
		DESTROY,
		NONE
	} type;

public:
	PlayerBullet(WeaponType type, bool isMove = true);
	~PlayerBullet();

	void Update();
	void Render();

	void EndEvent();
	void SetAction(int state);

	void Fire(Vector2 pos, Vector2 dir, float speed);

	WeaponType Type() { return weapontype; }
	bool IsFire() { return isFire; }
	bool& IsSelect() { return isSelect; }

private:
	WeaponType weapontype;
	StateType statetype = NONE;
	bool isFire = false;
	bool isMove = true;
	Collider* collider;
	Collider* colliderDamage = nullptr;

	float speed = 300.0f;
	Vector2 dir = {};
	float limitTime = 0.0f;

	float fireCooltime = 0.0f;

	bool isSelect = false;
	Character* selector;
	float invisibleTimer;
};