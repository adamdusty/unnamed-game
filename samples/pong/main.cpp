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

struct DrawInfo {
    std::array<int32_t, 2> quad;
};

auto movement_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Input, Position>();

    for(auto [entity, input, pos]: view.each()) {
        auto key = std::find(input.keys.begin(), input.keys.end(), SDLK_w);
        if(key != input.keys.end()) {
            input.keys.erase(key);
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

auto render_system(entt::registry &reg, SDL_Renderer *rend) -> void {
    auto view = reg.view<DrawInfo, Position>();

    SDL_RenderClear(rend);

    SDL_Rect rect{};

    for(auto [e, d, p]: view.each()) {
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        rect.w = d.quad.at(0);
        rect.h = d.quad.at(1);
        rect.x = p.x;
        rect.y = p.y;
        SDL_RenderFillRect(rend, &rect);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    }

    SDL_RenderPresent(rend);
}

auto create_paddle(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<Position>(ent, x, y);
    reg.emplace<DrawInfo>(ent, 10, 40);

    return ent;
}

auto main() -> int {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    auto reg = entt::registry{};

    SDL_Init(SDL_INIT_VIDEO);
    auto window =
        SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_RESIZABLE);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    create_paddle(reg, w * 0.1, h / 2);
    create_paddle(reg, w * 0.9, h / 2);

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int quit = 0;

    while(!quit) {
        t0 = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        input_system(reg, &quit);
        movement_system(reg, dt);
        render_system(reg, renderer);

        t1 = std::chrono::high_resolution_clock::now();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}