#include <chrono>
#include <iostream>
#include <vector>

#include "SDL.h"
#include "entt/entt.hpp"

struct Position {
    float x;
    float y;
};

struct Input {
    std::vector<SDL_KeyCode> keys;
};

auto movement_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<const Input, Position>();

    for(auto [entity, input, pos]: view.each()) {
        if(std::find(input.keys.begin(), input.keys.end(), SDLK_w) != input.keys.end()) {
            pos.y += 1;

            std::cout << pos.y << std::endl;
        }
    }
}

auto input_system(entt::registry &reg, int *quit) -> void {
    auto view = reg.view<Input>();
    SDL_Event ev{};
    if(SDL_PollEvent(&ev)) {
        switch(ev.type) {
        case SDL_QUIT:
            *quit = -1;
        case SDL_KEYDOWN:
            for(auto e: view) {
                auto &input = view.get<Input>(e);
                input.keys.emplace_back((SDL_KeyCode)ev.key.keysym.sym);
            }
            if(ev.key.keysym.sym == SDLK_ESCAPE) {
                *quit = -1;
            }
            break;
        }
    }
}

auto main() -> int {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    auto reg = entt::registry{};

    SDL_Init(SDL_INIT_VIDEO);
    auto window =
        SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_RESIZABLE);

    int quit = 0;

    while(!quit) {
        t0 = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        input_system(reg, &quit);
        movement_system(reg, dt);

        t1 = std::chrono::high_resolution_clock::now();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}