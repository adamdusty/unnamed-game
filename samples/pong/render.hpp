#pragma once

#include "entt/entt.hpp"
#include "image.hpp"
#include <cstdint>

namespace pong {

struct RenderSystem {
    virtual auto execute(entt::registry &reg, float dt) -> void = 0;
    virtual auto create_texture(const Image &img) -> uint32_t   = 0;
};

} // namespace pong