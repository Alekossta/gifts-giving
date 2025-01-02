#pragma once
#include <iostream>
#include <cmath>

class Vector2
{
    public:
        float x;
        float y;
        Vector2();
        Vector2(float newX, float newY);
        float GetMagnitude() const;
        void Normalize();
        float DistanceTo(const Vector2& otherVector);

        // Operator overloads
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};