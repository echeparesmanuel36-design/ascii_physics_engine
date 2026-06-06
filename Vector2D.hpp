#pragma once
#include <cmath>

struct Vector2D {
    float x, y;

    Vector2D(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    // Operaciones básicas de vectores
    Vector2D operator+(const Vector2D& other) const { return Vector2D(x + other.x, y + other.y); }
    Vector2D operator-(const Vector2D& other) const { return Vector2D(x - other.x, y - other.y); }
    Vector2D operator*(float scalar) const { return Vector2D(x * scalar, y * scalar); }
    
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Para calcular rebotes
    float dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D normalized() const {
        float len = length();
        if (len > 0) return *this * (1.0f / len);
        return Vector2D(0, 0);
    }
};
