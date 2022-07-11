#include "plugin.hpp"

extern "C" auto load_plugin() -> std::unique_ptr<Plugin> {
    return std::make_unique<Plugin>("test_plugin", std::array<uint32_t, 3>{0, 0, 1});
}
