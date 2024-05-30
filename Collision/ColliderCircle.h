#pragma once

class ColliderCircle : public Collider
{
public:
	ColliderCircle(float radius = 1.0f);
	~ColliderCircle();

	virtual void SetVertex() override;

	virtual bool Collision(Vector2 point) override;
	virtual bool Collision(ColliderRect* rect) override;
	virtual bool Collision(ColliderCircle* circle) override;

	float Radius() { return radius * max(GlobalScale().x, GlobalScale().y); }

private:
	float radius;

	const UINT sectorCount = 36;

};
