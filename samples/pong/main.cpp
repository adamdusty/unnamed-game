#include <chrono>
#include <iostream>

#include "SDL.h"
#include "comp.hpp"
#include "entt/entt.hpp"
#include "factories.hpp"
#include "sys.hpp"

namespace pong {

auto run_systems(entt::registry &reg, float dt, SDL_Renderer *rend) -> void {
    input_system(reg, dt);
    player_input_system(reg, dt);
    player_control_system(reg, dt);
    movement_system(reg, dt);
    collision_system(reg, dt);
    debug_system(reg, dt);
    render_system(reg, rend);
}

auto register_services() -> void {
    // entt::locator<b2World>::emplace(b2Vec2(0.0f, 0.0f));
}

} // namespace pong

using namespace pong;

auto main() -> int {
    auto t0  = std::chrono::high_resolution_clock::now();
    auto t1  = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    register_services();

    auto reg = entt::registry{};

    SDL_Init(SDL_INIT_VIDEO);
    auto window =
        SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_RESIZABLE);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    // create_paddle(reg, w * 0.9, h / 2);
    create_ball(reg, w / 2.0f, h / 2.0f);

    auto p = create_paddle(reg, w * 0.1, h / 2);
    reg.emplace<Player>(p);
    reg.emplace<Input>(p);
    reg.emplace<Debug>(p);

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event ev{};

    while(!quit) {
        t0 = std::chrono::high_resolution_clock::now();
        run_systems(reg, dt, renderer);

        t1 = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        dt *= 0.000001;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}