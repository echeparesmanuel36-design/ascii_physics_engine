#pragma once
#include "Vector2D.hpp"
#include <vector>

class Particle {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    char symbol;
    float friction = 0.99f; // Pérdida de energía en cada rebote
    float gravity = 0.5f;   // Fuerza hacia abajo

    Particle(float x, float y, float vx, float vy, char s = '*') 
        : position(x, y), velocity(vx, vy), acceleration(0, gravity), symbol(s) {}

    void update(float dt) {
        // Integración de Euler (Física básica)
        velocity += acceleration * dt;
        position += velocity * dt;
    }

    // Rebote contra los bordes de la consola (el "tanque")
    void check_bounds(int width, int height) {
        // Paredes laterales
        if (position.x <= 0) {
            position.x = 0;
            velocity.x *= -friction;
        } else if (position.x >= width - 1) {
            position.x = width - 1;
            velocity.x *= -friction;
        }

        // Suelo y techo
        if (position.y <= 0) {
            position.y = 0;
            velocity.y *= -friction;
        } else if (position.y >= height - 1) {
            position.y = height - 1;
            velocity.y *= -friction;
            // Pequeño truco para que no vibre en el suelo
            if (std::abs(velocity.y) < 0.1f) velocity.y = 0; 
        }
    }
};
