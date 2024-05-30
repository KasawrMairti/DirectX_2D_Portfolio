#pragma once

class ColliderRect : public Collider
{
public:
	ColliderRect(Vector2 size);
	~ColliderRect();

	virtual void SetVertex() override;

	virtual bool Collision(Vector2 point) override;
	virtual bool Collision(ColliderRect* rect) override;
	virtual bool Collision(ColliderCircle* circle) override;

	Vector2 GlobalSize() { return { size.x * globalScale.x, size.y * globalScale.y }; }

private:
	Vector2 size;
};
