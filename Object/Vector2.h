#pragma once

class Vector2 : public XMFLOAT2
{
public:
	Vector2();
	Vector2(float x, float y);

	float Length();

	Vector2 GetNormal();

	void Normalize();

	static float   Dot(const Vector2& v1, const Vector2& v2);
	static float Cross(const Vector2& v1, const Vector2& v2);

	static bool IsBetween(Vector2 factor, Vector2 v1, Vector2 v2);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;

	Vector2 operator*(const float& value) const;
	Vector2 operator/(const float& value) const;

	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);

	void operator*=(const float& value);
	void operator/=(const float& value);

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);

	static float Distance(Vector2 p1, Vector2 p2);

	Vector2 operator*(const Matrix& value) const;

	static Vector2 Lerp(const Vector2& start, const Vector2& end, const float& factor);
};
