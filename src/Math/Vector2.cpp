#include "Math/Vector2.h"

Vector2::Vector2() : x(0), y(0)
{

}

Vector2::Vector2(float newX, float newY) : x(newX), y(newY)
{

}

float Vector2::GetMagnitude() const
{
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::operator/(float scalar) const
{
    if(scalar != 0)
    {
        return Vector2(x / scalar, y / scalar);
    }
    else // if scalar is 0 just return the same vector
    {
        return *this;
    }
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

void Vector2::Normalize()
{
    float magnitude = GetMagnitude();
    if(magnitude > 0)
    {
        *this = *this / magnitude;
    }
}

float Vector2::DistanceTo(const Vector2& otherVector)
{
    float dx = x - otherVector.x;
    float dy = y - otherVector.y;
    return std::sqrt(dx*dx + dy*dy);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}