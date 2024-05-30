#pragma once

class Camera : public Singleton<Camera>
{
	friend class Singleton;
private:
	Camera();
	~Camera();
	
public:
	struct Area
	{
		float L = 0.0f;
		float R = WIN_WIDTH;
		float T = WIN_HEIGHT;
		float B = 0.0f;

		Area(float L, float R, float T, float B) :L(L), R(R), T(T), B(B) { };
	};

public:
	void Update();

	void   FreeMode();
	void TargetMode();

	void SetTranslation(Transform* target);

	void SetTarget(Transform* target, float speed) { this->target = target; this->speed = speed; }
	void SetOffset(Vector2    offset) { this->offset = offset; }

	Transform* GetTransform() { return transform; }

	vector<Area>& Areas() { return area; }


private:
	Transform* transform = nullptr;

	MatrixBuffer* vBuffer;

	Transform* target = nullptr;

	float speed = 100.0f;

	Vector2 offset = WIN_CENTER;

	struct vector<Area> area;
};
