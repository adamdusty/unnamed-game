#include "factories.hpp"

#include "collision.hpp"
#include "comp.hpp"
#include "fmt/format.h"
#include "image.hpp"
#include "sys.hpp"
#include <cstdint>
#include <random>

namespace pong {

auto create_paddle(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();

    auto img     = load_image("/home/ad/Pictures/paddle.png");
    auto texture = entt::locator<RenderSystem>::value().create_texture(img);

    reg.emplace<SDLDrawInfo>(ent, texture, static_cast<uint32_t>(img.width), static_cast<uint32_t>(img.height));
    reg.emplace<Transform>(ent, x, y, 0.0f);
    reg.emplace<Velocity>(ent);
    auto c = reg.emplace<PolygonCollider>(ent, box_collider(0, 0, 32.0f, 32.0f * 8));

    return ent;
}

auto create_ball(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    // reg.emplace<DrawInfo>(ent, 32.0f, 32.0f);
    reg.emplace<Transform>(ent, x, y, 0.0f);
    reg.emplace<Velocity>(ent, 0.0f, 0.0f);
    // reg.emplace<PolygonCollider>(ent, box_collider(0.0f, 0.0f, 32.0f, 32.0f));

    return ent;
}

} // namespace pong