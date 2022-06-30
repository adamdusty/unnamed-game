#pragma once

#include "comp.hpp"
#include "entt/entt.hpp"
#include "image.h"
#include <cstdint>
#include <unordered_map>

namespace pong {

struct RenderSystem {

    RenderSystem(SDL_Window *window);
    auto run(entt::registry &reg, float dt) -> void;
    auto cleanup() -> void;
    auto create_texture(const Image &img) -> uint32_t;

    SDL_Renderer *renderer;
    std::unordered_map<uint32_t, SDL_Texture *> texture_map;
    uint32_t next_texture;
};

auto player_input_system(entt::registry &reg, float dt) -> void;
auto input_system(entt::registry &reg, float dt) -> void;
auto player_control_system(entt::registry &reg, float dt) -> void;
auto movement_system(entt::registry &reg, float dt) -> void;
auto collision_system(entt::registry &reg, float dt) -> void;
auto debug_system(entt::registry &reg, float dt) -> void;

} // namespace pong