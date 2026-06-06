# 🕹️ ASCII Physics Engine 2D

A lightweight, real-time 2D physics engine that renders directly in your terminal using ASCII characters. Written in pure C++17.

## ✨ Features

* **Real-time Physics:** Implements basic semi-implicit Euler integration for movement.
* **Vector Mathematics:** Custom 2D Vector class for position, velocity, and acceleration.
* **Collision Detection:** Basic AABB collision against terminal boundaries with energy loss (friction/restitution).
* **ASCII Rendering:** Efficient screen buffering and rendering using standard terminal output.
* **Zero Dependencies:** Uses only the C++ Standard Library.

## 🚀 Quick Start

### Prerequisites

* A C++17 compatible compiler (GCC, Clang, MSVC).
* CMake (version 3.10 or higher).

### Build & Run

## 1. Clone the repository:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/ascii_physics_engine.git](https://github.com/YOUR_USERNAME/ascii_physics_engine.git)
   cd ascii_physics_engine
```

## 2.Create a build directory and configure:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```
## 3.Build the project:
```bash
cmake --build
```

### Run the engine:

​Linux/Mac: 
```bash
./ascii_physics
```
​Windows: 
```bash
ascii_physics.exe
```

## 🛠️ How it Works
1.​Update: Calculates new positions and velocities based on gravity and delta time (dt).

2.​Resolve: Checks if particles collide with the screen edges and calculates the bounce using a friction coefficient.

3.​Render: Draws the current state of all particles into a screen buffer (a vector of strings) and prints it to the terminal.

​📄 License
​This project is open-source and free to use under the MIT License.