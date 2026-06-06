#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include <memory>

// ==========================================
// 1. INFRAESTRUCTURA MATEMÁTICA DEL MOTOR
// ==========================================
struct Vector2 {
    float x, y;
    Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}
    Vector2 operator+(const Vector2& o) const { return Vector2(x + o.x, y + o.y); }
    Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
    Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }
};

// ==========================================
// 2. LA ENTIDAD BASE (Para que hagan lo que quieran)
// ==========================================
class Entity {
public:
    Vector2 position;
    Vector2 velocity;
    char symbol;
    bool has_gravity;

    Entity(float x, float y, char s, bool gravity = true) 
        : position(x, y), velocity(0, 0), symbol(s), has_gravity(gravity) {}
    
    virtual ~Entity() = default;

    // Física genérica heredable
    virtual void update(float dt, float gravity_value) {
        if (has_gravity) {
            velocity.y += gravity_value * dt;
        }
        position += velocity * dt;
    }
};

// ==========================================
// 3. EL CORE DEL MOTOR (Framework Abstracto)
// ==========================================
class AsciiEngine {
protected:
    int width;
    int height;
    bool is_running;
    float gravity;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::string> screen_buffer;

    void clear_screen() {
#ifdef _WIN32
        std::system("cls");
#else
        std::cout << "\033[2J\033[1H"; // Limpieza rápida ANSI Linux/Mac
#endif
    }

public:
    AsciiEngine(int w, int h) : width(w), height(h), is_running(false), gravity(0.4f) {
        screen_buffer.resize(height, std::string(width, ' '));
    }

    virtual ~AsciiEngine() = default;

    // Métodos de control para el usuario
    void spawn_entity(std::unique_ptr<Entity> entity) {
        entities.push_back(std::move(entity));
    }

    void set_gravity(float g) { gravity = g; }
    void stop() { is_running = false; }

    // ==========================================
    // HOOKS/INTERFACES: Aquí el usuario mete su lógica
    // ==========================================
    virtual void on_start() = 0;
    virtual void on_update(float dt) = 0; 

    // ==========================================
    // BUCLE PRINCIPAL (Game Loop Oculto)
    // ==========================================
    void start() {
        is_running = true;
        on_start(); // Inicializa el juego del usuario

        auto last_time = std::chrono::high_resolution_clock::now();

        while (is_running) {
            auto current_time = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<double, std::milli>(current_time - last_time).count() / 100.0f;
            last_time = current_time;

            // A) Lógica personalizada del usuario
            on_update(dt);

            // B) Sistema de físicas interno del motor
            for (auto& e : entities) {
                e->update(dt, gravity);
                
                // Colisiones por defecto con los bordes del mundo
                if (e->position.x < 0) { e->position.x = 0; e->velocity.x *= -0.8f; }
                if (e->position.x >= width) { e->position.x = width - 1; e->velocity.x *= -0.8f; }
                if (e->position.y < 0) { e->position.y = 0; e->velocity.y *= -0.8f; }
                if (e->position.y >= height) { e->position.y = height - 1; e->velocity.y *= -0.8f; }
            }

            // C) Renderizado automático en el Buffer
            for (auto& row : screen_buffer) {
                std::fill(row.begin(), row.end(), ' '); // Limpiar frame anterior
            }

            for (const auto& e : entities) {
                int x = static_cast<int>(std::round(e->position.x));
                int y = static_cast<int>(std::round(e->position.y));
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    screen_buffer[y][x] = e->symbol;
                }
            }

            // D) Dibujar en pantalla de golpe (evita parpadeo)
            clear_screen();
            std::string frame = "";
            for (const auto& row : screen_buffer) {
                frame += row + '\n';
            }
            std::cout << frame;

            std::this_thread::sleep_for(std::chrono::milliseconds(33)); // ~30 FPS
        }
    }
};

// ==========================================
// 4. EJEMPLO DE CÓMO EL USUARIO USA TU MOTOR
// ==========================================
// El usuario solo tiene que hacer esto para crear un "Juego" o simulación:
class MiJuegoPersonalizado : public AsciiEngine {
public:
    MiJuegoPersonalizado() : AsciiEngine(80, 20) {}

    // Configura sus elementos al arrancar
    void on_start() override {
        // Añade una entidad controlada o con físicas
        auto jugador = std::make_unique<Entity>(10.0f, 2.0f, '@', true);
        jugador->velocity = Vector2(4.0f, 0.0f); // Le da un empujón inicial a la derecha
        spawn_entity(std::move(jugador));

        // Añade otra cosa estática en el aire (sin gravedad)
        auto plataforma = std::make_unique<Entity>(40.0f, 10.0f, '#', false);
        spawn_entity(std::move(plataforma));
    }

    // Modifica las reglas en tiempo real si quiere
    void on_update(float dt) override {
        // Aquí el usuario podría leer inputs, cambiar eventos, crear enemigos, etc.
        // Por ahora, el motor hace todo el trabajo de física automáticamente.
    }
};

int main() {
    // El usuario final solo inicializa su juego y arranca el motor
    MiJuegoPersonalizado juego;
    juego.set_gravity(0.6f); // Puede tunear el motor
    juego.start();           // El motor toma el control
    return 0;
}
