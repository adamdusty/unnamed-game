#include "sdk.hpp"

#include "entt/entt.hpp"
#include "fmt/format.h"

auto main() -> int {
    using namespace ung::sdk;
    auto plugin = load_plugin("/home/ad/dev/unnamed-game/build/debug/lib/libplugin.so");

    auto reg = entt::registry{};

    for(auto &sys: plugin->systems) {
        sys->execute(reg, 0.f);
    }

    return 0;
}