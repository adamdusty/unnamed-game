#pragma once

#include "comp.hpp"
#include "entt/entt.hpp"

namespace pong {

struct RenderSystem {

    RenderSystem(SDL_Window *window);
    auto run(entt::registry &reg, float dt) -> void;
    auto cleanup() -> void;

    SDL_Renderer *renderer;
};

auto player_input_system(entt::registry &reg, float dt) -> void;
auto input_system(entt::registry &reg, float dt) -> void;
auto player_control_system(entt::registry &reg, float dt) -> void;
auto movement_system(entt::registry &reg, float dt) -> void;
auto collision_system(entt::registry &reg, float dt) -> void;
auto debug_system(entt::registry &reg, float dt) -> void;

} // namespace pong