#include "Framework.h"
#include "Vector2.h"

Vector2::Vector2()
    :XMFLOAT2()
{
}

Vector2::Vector2(float x, float y)
    :XMFLOAT2(x, y)
{
}

float Vector2::Length()
{
    return sqrtf(powf(x, 2) + powf(y, 2));
    //sqrt(x*x + y*y);
}

Vector2 Vector2::GetNormal()
{
    return *this / Length();
}

void Vector2::Normalize()
{
    *this /= Length();
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2)
{
    return (v1.x * v2.y - v2.x * v1.y);
}

bool Vector2::IsBetween(Vector2 factor, Vector2 v1, Vector2 v2)
{
    return (factor.x * v1.y - v1.x * factor.y) * (factor.x * v2.y - v2.x * factor.y) < 0;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(this->x * value, this->y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
    return Vector2(this->x / value, this->y / value);
}

void Vector2::operator+=(const Vector2& other)
{
    this->x += other.x;
    this->y += other.y;
}

void Vector2::operator-=(const Vector2& other)
{
    this->x -= other.x;
    this->y -= other.y;
}

void Vector2::operator*=(const float& value)
{
    this->x *= value;
    this->y *= value;
}

void Vector2::operator/=(const float& value)
{
    this->x /= value;
    this->y /= value;
}

bool Vector2::operator==(const Vector2& other)
{
    if (this->x == other.x && this->y == other.y)
        return true;
    else
        return false;
}

bool Vector2::operator!=(const Vector2& other)
{
    if (this->x == other.x && this->y == other.y)
        return false;
    else
        return true;
}

float Vector2::Distance(Vector2 p1, Vector2 p2)
{
    return sqrtf(powf(p2.x - p1.x, 2) + powf(p2.y - p1.y, 2));
}

Vector2 Vector2::operator*(const Matrix& value) const
{
    XMVECTOR vector = XMLoadFloat2(this);

    vector = XMVector2TransformCoord(vector, value);

    Vector2 position;
    XMStoreFloat2(&position, vector);

    return position;
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, const float& factor)
{
    return start + (end - start) * factor;
}
