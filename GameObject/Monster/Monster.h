#pragma once

class Monster : public Character
{
public:
	enum State
	{
		IDLE,
		SPAWN,
		MOVE,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		ATTACK4,
		ATTACK5,
		ATTACK6,
		ATTACK7,
		ATTACK8,
		ATTACK9,
		ATTACK10,
		DIE,
		NONE
	};

	enum MonsterType
	{
		LV1, LV2, LV3
	};

public:
	Monster();
	~Monster();

	void Update();
	void Render();

	bool PlayerCheck();

	void SetAction(int state);

	virtual void Damaged(float damaged) = 0;

	bool& IsPlay() { return isPlay; }
	float& SetHP() { return stat_HP; }
	MonsterType Type() { return type; }

	Collider* GetBody() { return body;	}

protected:
	void IsPlayed(bool boolean) { isPlay = boolean; }

protected:
	MonsterType type;
	bool isPlay = true;
	State state = MOVE;

	Collider* senser = nullptr;
	Collider* body = nullptr;

	// Move
	bool isRight = false;
	bool sensorRight = false;
	bool isAttackRight = false;
	bool checkPlayer = false;
	float moveSpeed = 0.0f;
	float movePower = 500.0f;

	// Stat
	float stat_HP = 1.0f;
	float damagedTime = 0.0f;

	// Time
	float AttackCoolTime = 0.0f;
	float AttackCoolTimeMax = 1.0f;
};