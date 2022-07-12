#pragma once

#include "entt/entt.hpp"
#include <SDL.h>

namespace ung {
namespace sdk {

struct System {
    virtual ~System() {}

    virtual auto init(SDL_Window *window) -> void               = 0;
    virtual auto execute(entt::registry &reg, float dt) -> void = 0;
};

} // namespace sdk
} // namespace ung