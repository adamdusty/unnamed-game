#include "sdk.hpp"

#include "entt/entt.hpp"
#include "fmt/format.h"

auto main() -> int {
    using namespace ung::sdk;
    PluginService plugin_service{};
    plugin_service.load_plugin("/home/ad/dev/unnamed-game/build/debug/lib/libplugin.so");

    auto reg = entt::registry{};

    for(auto &p: plugin_service.plugins) {
        for(auto &sys: p.systems) {
            sys->execute(reg, 0.f);
        }
    }

    fmt::print("Should end succesfully\n");
    return 0;
}