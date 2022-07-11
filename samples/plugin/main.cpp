#include "sdk.hpp"

#include "fmt/format.h"

auto main() -> int {
    using namespace ung::sdk;
    auto plugin = load_plugin("/home/ad/dev/unnamed-game/build/debug/lib/libplugin.so");

    fmt::print("{}\n", plugin->name);
    fmt::print("{}, {}, {}\n", plugin->version.at(0), plugin->version.at(1), plugin->version.at(2));

    return 0;
}