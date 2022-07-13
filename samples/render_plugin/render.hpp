#include "sdk.hpp"
#include <SDL.h>
#include <fmt/format.h>

#include "render_plugin/render_plugin_export.hpp"

using namespace ung::sdk;
namespace rp {
extern "C" RENDER_PLUGIN_EXPORT auto load_plugin() -> Plugin;

struct RenderSystem : public System {
    ~RenderSystem() { SDL_DestroyRenderer(renderer); }

    auto init(SDL_Window *window) -> void override {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    auto execute(entt::registry &reg, float dt) -> void override {
        // fmt::print("RENDERING\n");
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Renderer *renderer;
};
} // namespace rp