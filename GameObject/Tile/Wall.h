#pragma once

class Wall : public Transform
{
public:
	enum Type
	{
		TOP, BOTTOM, LEFT, RIGHT
	};

public:
	Wall(Vector2 size, Type type);
	~Wall();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }
	Type GetType() { return type; }

private:
	Collider* collider;

	Type type;
};