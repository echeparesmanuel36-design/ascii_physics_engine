#pragma once
#include "Vector2D.hpp"

// La clase base para CUALQUIER cosa que el usuario quiera crear en el motor
class Entity {
public:
    Vector2D position;
    Vector2D velocity;
    char symbol;
    bool has_gravity;

    Entity(float x, float y, char s, bool gravity = true) 
        : position(x, y), velocity(0, 0), symbol(s), has_gravity(gravity) {}
    
    virtual ~Entity() = default;

    // Física del motor que hereda cada objeto
    virtual void update(float dt, float gravity_value) {
        if (has_gravity) {
            velocity.y += gravity_value * dt;
        }
        position += velocity * dt;
    }
};
