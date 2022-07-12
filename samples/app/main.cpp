#include "sdk.hpp"
#include <SDL2/SDL.h>
#include <fmt/format.h>

auto main() -> int {
    using namespace ung::sdk;

    auto plugin_service = PluginService{};

    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow(
        "Test Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);

    plugin_service.load_plugin("/home/ad/dev/unnamed-game/build/debug/lib/librender_plugin.so");
    plugin_service.initialize_plugins(window);

    auto reg = entt::registry{};

    SDL_Event ev{};
    bool exit = false;
    while(!exit) {
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
            case SDL_QUIT:
                exit = true;
            }
        }

        for(auto &p: plugin_service.plugins) {
            for(auto &s: p.systems) {
                s->execute(reg, 0.f);
            }
        }
    }
}