#pragma once

class Monster_lv1Attack : public Character
{
public:
	Monster_lv1Attack();
	~Monster_lv1Attack();

	void Update();
	void Render();

	void Fire(Vector2 pos, Vector2 dir, float speed);
	void Hit();

	void SetAction(int state);

	bool IsFire() { return isFire; }
	Collider* GetCollider() { return collider; }
	Vector2& Dir() { return dir; }

private:
	void IsFired() { isFire = false; isDestroyed = false; }

private:
	bool isFire = false;
	bool isDestroyed = false;

	float speed = 300.0f;
	Vector2 dir = {};
	int state = 0;

	float timelimit = 0.0f;

	Collider* collider;

};