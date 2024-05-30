#pragma once

class Transform
{
public:
	Transform();
	~Transform();

	virtual void Update();
	
	virtual void UpdateWorld();

	Vector2& Scale()       { return lScale; }
	Vector3& Rotation()    { return lRotation; }
	Vector2& Translation() { return lTranslation; }

	Matrix& GetWorld() { return world; }

	Matrix& GetT() { return T; }

	bool& IsActive() { return isActive; }

	void SetParent(Transform* parent) { this->parent = parent; }

	Vector2 GlobalScale()    { return globalScale; }
	Vector2 GlobalPosition() { return globalPosition; }

	void Debug(); 
	void Debug(string label);

	void SetLabel(string  label) { this->label = label; }
	void SetPivot(Vector2 pivot) { this->pivot = pivot; }

	Vector2 Right() { return right; }
	Vector2    Up() { return    up; }

protected:
	bool isActive = true;

	Vector2 lScale       = Vector2(1.0f, 1.0f);
	Vector3 lRotation    = Vector3(0.0f, 0.0f, 0.0f);
	Vector2 lTranslation = Vector2(0.0f, 0.0f);

	Matrix S, R, T;
	Matrix world;

	Transform* parent = nullptr;

	Vector2 globalPosition;
	Vector2 globalScale;

	string label = "";

	Vector2 pivot;

	Matrix P, IP;

	Vector2 right, up;
};
