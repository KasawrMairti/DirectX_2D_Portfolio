#include "Framework.h"
#include "ColliderRect.h"

ColliderRect::ColliderRect(Vector2 size)
	:size(size)
{
	SetVertex();

	type = RECT;
}

ColliderRect::~ColliderRect()
{
}

void ColliderRect::SetVertex()
{
	float L = -size.x * 0.5f;
	float R = +size.x * 0.5f;
	float B = -size.y * 0.5f;
	float T = +size.y * 0.5f;

	vertices =
	{
		Vector2(L, T),
		Vector2(R, T),
		Vector2(R, B),
		Vector2(L, B),
		Vector2(L, T),
	};

	vertexBuffer = new VertexBuffer(vertices);
}

bool ColliderRect::Collision(Vector2 point)
{
	Matrix invWorld = XMMatrixInverse(nullptr, world);

	Vector2 invPoint = point * invWorld;

	if (abs(invPoint.x) < size.x * 0.5f && abs(invPoint.y) < size.y * 0.5f)
		return true;

	return false;
}

bool ColliderRect::Collision(ColliderRect* rect)
{
	Vector2 distance = this->globalPosition - rect->globalPosition;

	Vector2 axes[4] =
	{
		this->right,
		this->up,
		rect->right,
		rect->up
	};

	Vector2 vectors[4] =
	{
		axes[0] * (this->GlobalSize().x * 0.5f),
		axes[1] * (this->GlobalSize().y * 0.5f),
		axes[2] * (rect->GlobalSize().x * 0.5f),
		axes[3] * (rect->GlobalSize().y * 0.5f),
	};

	for (UINT i = 0; i < 4; i++)
	{
		float sum = 0;

		for (UINT j = 0; j < 4; j++)
		{
			sum += abs(Vector2::Dot(axes[i], vectors[j]));
		}

		if (sum <= abs(Vector2::Dot(axes[i], distance)))
			return false; 
	}

	return true;
}

bool ColliderRect::Collision(ColliderCircle* circle)
{
	Vector2 distance = this->globalPosition - circle->GlobalPosition();

	Vector2 axes[2] =
	{
		this->right,
		this->up
	};

	Vector2 vectors[2] =
	{
		axes[0] * this->GlobalSize().x * 0.5f,
		axes[1] * this->GlobalSize().y * 0.5f,
	};

	float lengthX = abs(Vector2::Dot(axes[0], distance));
	float lengthY = abs(Vector2::Dot(axes[1], distance));

	float radius = circle->Radius();

	if (lengthX > this->GlobalSize().x * 0.5f + radius) return false;
	if (lengthY > this->GlobalSize().y * 0.5f + radius) return false;

	if (lengthX < this->GlobalSize().x * 0.5f) return true;
	if (lengthY < this->GlobalSize().y * 0.5f) return true;

	float x = lengthX - this->GlobalSize().x * 0.5f;
	float y = lengthY - this->GlobalSize().y * 0.5f;

	float edgeToCircle = sqrt(pow(x, 2) + pow(y, 2));

	return edgeToCircle < radius;
}

