#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "entt/entt.hpp"
#include "system.hpp"
#include <SDL2/SDL.h>

namespace ung {
namespace sdk {

struct Plugin {

    Plugin(const char *name, std::array<uint32_t, 3> version) : name(name), version(version) {}

    std::string name;
    std::array<uint32_t, 3> version;
    std::vector<std::unique_ptr<System>> systems;
};

struct PluginService {
    ~PluginService();
    auto load_plugin(const char *path) -> void;
    auto initialize_plugins(SDL_Window *window) -> void;

    std::vector<Plugin> plugins;
    std::vector<void *> plugin_libs;
};

} // namespace sdk
} // namespace ung
