#pragma once

#include "entt/entt.hpp"

namespace pong {

auto create_paddle(entt::registry &reg, float x, float y) -> entt::entity;
auto create_ball(entt::registry &reg, float x, float y) -> entt::entity;

} // namespace pong