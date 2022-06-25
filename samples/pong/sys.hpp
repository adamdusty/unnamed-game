#pragma once

#include "box2d/box2d.h"
#include "comp.hpp"
#include "entt/entt.hpp"

namespace pong {

auto player_input_system(entt::registry &reg, float dt) -> void;
auto render_system(entt::registry &reg, SDL_Renderer *rend) -> void;
auto physics_system(entt::registry &reg, float dt) -> void;
auto input_system(entt::registry &reg, float dt) -> void;
auto player_control_system(entt::registry &reg, float dt) -> void;

} // namespace pong