#pragma once

#include <SDL.h>
#include "SDL2/SDL_image.h"
#include "entt/entt.hpp"
#include <array>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

struct Position {
    float x;
    float y;
};

struct Transform {
    Position position;
    float rotation;
};

struct Debug {
    int dummy;
};

struct Velocity {
    float x;
    float y;
    float rotational;
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

struct SDLDrawInfo {
    uint32_t texture;
    uint32_t width;
    uint32_t height;
};

// Paddle
//  - Transform
//  - Velocity
//  - Texture