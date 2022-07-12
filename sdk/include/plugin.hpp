#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "entt/entt.hpp"
#include "system.hpp"

namespace ung {
namespace sdk {

struct Plugin {

    Plugin(const char *name, std::array<uint32_t, 3> version) : name(name), version(version) {}

    std::string name;
    std::array<uint32_t, 3> version;
    std::vector<std::unique_ptr<System>> systems;
};

auto load_plugin(const char *path) -> std::unique_ptr<Plugin>;

} // namespace sdk
} // namespace ung
