#pragma once

#include "entt/entt.hpp"

namespace ung {
namespace sdk {

struct System {
    virtual ~System() {}

    virtual auto init(entt::registry &reg) -> void              = 0;
    virtual auto execute(entt::registry &reg, float dt) -> void = 0;
};

} // namespace sdk
} // namespace ung