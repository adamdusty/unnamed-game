#include "render.hpp"

#include <sdk.hpp>

namespace rp {

auto load_plugin() -> Plugin {
    std::unique_ptr<System> render_sys = std::make_unique<RenderSystem>();

    Plugin p{"RenderPlugin", {1, 0, 0}};
    p.systems.emplace_back(std::move(render_sys));

    return p;
}

} // namespace rp