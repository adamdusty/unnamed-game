#include "plugin.hpp"

extern "C" auto load_plugin() -> std::unique_ptr<Plugin> {
    std::unique_ptr<System> sys = std::make_unique<TestSystem>();
    auto plugin                 = std::make_unique<Plugin>("test_plugin", std::array<uint32_t, 3>{0, 0, 1});
    plugin->systems.emplace_back(std::move(sys));

    return plugin;
}
