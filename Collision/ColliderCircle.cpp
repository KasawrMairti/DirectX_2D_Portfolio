#include "Framework.h"
#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(float radius)
	:radius(radius)
{
	SetVertex();

	type = CIRCLE;
}

ColliderCircle::~ColliderCircle()
{
}

void ColliderCircle::SetVertex()
{
	for (UINT i = 0; i <= sectorCount; i++)
	{
		float angle = XM_2PI / sectorCount * i;

		Vector2 position =
		{
			cosf(angle) * radius,
			sinf(angle) * radius
		};

		vertices.push_back(Vertex(position));
	}

	vertexBuffer = new VertexBuffer(vertices);
}

bool ColliderCircle::Collision(Vector2 point)
{
	float distance = Vector2::Distance(point, GlobalPosition());

	return distance < Radius();
}

bool ColliderCircle::Collision(ColliderRect* rect)
{
	return rect->Collision(this);
}

bool ColliderCircle::Collision(ColliderCircle* circle)
{
	float distance = Vector2::Distance(circle->GlobalPosition(), this->GlobalPosition());

	return distance < circle->Radius() + this->Radius();
}

