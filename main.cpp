#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include "Particle.hpp"

// Configuración de la pantalla ASCII
const int WIDTH = 80;
const int HEIGHT = 24;

// Función para limpiar la pantalla de forma eficiente
void clear_screen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1H"; // Códigos de escape ANSI para Linux/Mac
#endif
}

int main() {
    std::cout << "Starting ASCII Physics Engine...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Crear partículas con posiciones y velocidades aleatorias
    std::vector<Particle> particles;
    char symbols[] = {'*', 'o', '@', '+', '#'};
    
    for (int i = 0; i < 50; ++i) {
        particles.emplace_back(
            static_cast<float>(rand() % WIDTH),       // X aleatoria
            static_cast<float>(rand() % (HEIGHT / 2)), // Y aleatoria (mitad superior)
            static_cast<float>((rand() % 10) - 5),    // VX aleatoria
            static_cast<float>((rand() % 5) - 2),     // VY aleatoria
            symbols[rand() % 5]                       // Símbolo aleatorio
        );
    }

    auto last_time = std::chrono::high_resolution_clock::now();

    // Bucle principal del motor (Game Loop)
    while (true) {
        auto current_time = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<double, std::milli>(current_time - last_time).count() / 100.0f; // Delta Time simplificado
        last_time = current_time;

        // 1. Actualizar Física
        for (auto& p : particles) {
            p.update(dt);
            p.check_bounds(WIDTH, HEIGHT);
        }

        // 2. Renderizar (Dibujar en el buffer)
        std::vector<std::string> screen(HEIGHT, std::string(WIDTH, ' '));

        // Dibujar partículas en el buffer
        for (const auto& p : particles) {
            int x = static_cast<int>(std::round(p.position.x));
            int y = static_cast<int>(std::round(p.position.y));

            // Asegurar que estamos dentro del rango antes de dibujar
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                screen[y][x] = p.symbol;
            }
        }

        // 3. Imprimir buffer en la consola
        clear_screen();
        std::string frame = "";
        for (const auto& row : screen) {
            frame += row + '\n';
        }
        std::cout << frame;

        // Controlar FPS (aprox 30-60 fps)
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    return 0;
}
