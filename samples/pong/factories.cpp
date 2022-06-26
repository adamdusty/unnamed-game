#include "factories.hpp"

#include "collision.hpp"
#include "comp.hpp"
#include <random>

namespace pong {

auto create_paddle(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<DrawInfo>(ent, 32.0f, 32.0f * 8);
    reg.emplace<Position>(ent, x, y);
    reg.emplace<Velocity>(ent);
    reg.emplace<PolygonCollider>(ent, box_collider(0, 0, 32.0f, 32.0f * 8));

    return ent;
}

auto create_ball(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<DrawInfo>(ent, 32.0f, 32.0f);
    reg.emplace<Position>(ent, x, y);
    reg.emplace<Velocity>(ent, -128.0f, 0.0f);
    reg.emplace<PolygonCollider>(ent, box_collider(0.0f, 0.0f, 32.0f, 32.0f));

    return ent;
}

} // namespace pong