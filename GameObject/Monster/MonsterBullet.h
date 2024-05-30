#pragma once

class MonsterBullet : public Character
{
public:
	MonsterBullet();
	~MonsterBullet();

	void Update();
	void Render();

	void Move();
	void Hit();
	void EndEvent();

	void AddAction();
	void SetAction(int state);

	void Fire(Vector2 pos, Vector2 dir, float speed);
	bool IsFire() { return isFire; }

private:
	bool isFire = false;
	int state = 0;
	Collider* collider;

	bool stopping = false;
	float speed = 300.0f;
	Vector2 dir = {};
	float limitTime = 0.0f;
	float gravity = 0.0f;

	Vector2 originalScale;
};