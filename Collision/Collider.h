#pragma once

class Collider : public Transform
{
protected:
	enum Type
	{
		RECT,
		CIRCLE
	} type;

public:
	Collider();
	~Collider();

	void Render();

	virtual void SetVertex() = 0;

	bool Collision(Collider* other);

	virtual bool Collision(Vector2 point) = 0;
	virtual bool Collision(class ColliderRect* rect) = 0;
	virtual bool Collision(class ColliderCircle* circle) = 0;

	void SetColor(float r, float g, float b) { colorBuffer->SetData(r, g, b); }

	virtual Vector2 GlobalSize() { return Vector2(); }

	virtual float L() { return globalPosition.x - GlobalSize().x * 0.5f; }
	virtual float R() { return globalPosition.x + GlobalSize().x * 0.5f; }
	virtual float B() { return globalPosition.y - GlobalSize().y * 0.5f; }
	virtual float T() { return globalPosition.y + GlobalSize().y * 0.5f; }

	static void HiddenInGame() { hiddenInGame = !hiddenInGame; }

	static bool hiddenInGame;

protected:
	vector<Vertex> vertices;

	VertexBuffer* vertexBuffer;

	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	 MatrixBuffer* worldBuffer;
	  ColorBuffer* colorBuffer;
};
