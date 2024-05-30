#pragma once

class Player : public Character
{
	enum State
	{
		IDLE,
		IDLEUP,
		RUN,
		RUNUP,
		JUMP,
		JUMPING,
		JUMPUP,
		JUMPINGUP,
		JUMPDOWN,
		JUMPINGDOWN,
		SIT,
		SITTING,
		SITWALK,
		DIE,
		DIED
	};

public:
	Player();
	~Player();

	void Update();
	void Render();

	void Damaged(UINT damage, bool isRight);
	void DamageEvent();

	bool& IsPlay() { return isPlay; }
	bool IsRight() { return isRight; }
	Collider* GetCollider() { return collider; }

	UINT& WeaponCount() { return weaponCount; }

private:
	void Move();
	void Jump();
	void Attack();

	void GravityStop();

	void AddAction();
	void SetAction(int state);

private:
	bool isPlay = true;
	Collider* collider;

	State state = State::IDLE;

	// Move
	bool isRight = true;
	float moveSpeed = 0.0f;
	float movePower = 150.0f;

	// Jump
	UINT jumpCount = 0;
	bool jumping = false;
	float gravity = 0.0f;
	float gravityPower = 980.0f;
	float jumpSpeed = 0.0f;
	float jumpPower = 450.0f;

	// Status
	UINT stat_HP = 3;

	// Weapon
	PlayerBulletManager* bullets;
	UINT weaponCount = 1;

	// Damaged
	bool damaged = false;
	bool damageRight = false;
	float damageTime = 0.0f;

};