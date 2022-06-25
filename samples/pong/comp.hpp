#pragma once

#include "SDL.h"
#include "entt/entt.hpp"
#include <array>
#include <functional>
#include <memory>
#include <vector>

struct Position {
    float x;
    float y;
};

struct Velocity {
    float x;
    float y;
};

struct Input {
    std::vector<SDL_Scancode> keys_down;
    std::vector<SDL_Scancode> keys_up;

    auto clear() -> void {
        keys_down.clear();
        keys_up.clear();
    }
};

struct Player {
    std::array<float, 2> axis_input;
};

struct DrawInfo {
    std::array<float, 2> quad;
};