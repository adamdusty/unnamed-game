#include <chrono>
#include <iostream>
#include <optional>
#include <vector>

#include "SDL.h"
#include "entt/entt.hpp"

struct Velocity {
    float x;
    float y;
};

struct Position {
    float x;
    float y;
};

struct Input {
    std::vector<SDL_Scancode> keys_down;
    std::vector<SDL_Scancode> keys_up;
};

struct Player {
    std::array<float, 2> axis_input;
};

struct DrawInfo {
    std::array<int32_t, 2> quad;
};

auto movement_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Position, Velocity>();

    for(auto [entity, pos, vel]: view.each()) {
        if(vel.y != 0) {
            std::cout << vel.y << '\n';
        }
        pos.x += vel.x * 250 * dt;
        pos.y += vel.y * 250 * dt;
    }
}

auto player_input_system(entt::registry &reg, const Input input) -> void {
    auto view = reg.view<Player, Velocity>();

    for(auto [e, p, v]: view.each()) {
        for(auto k: input.keys_down) {
            switch(k) {
            case SDL_SCANCODE_W:
                v.y = -1;
                break;
            case SDL_SCANCODE_S:
                v.y = 1;
                break;
            default:
                break;
            }
        }

        for(auto k: input.keys_up) {
            switch(k) {
            case SDL_SCANCODE_W:
                v.y = 0;
                break;
            case SDL_SCANCODE_S:
                v.y = 0;
                break;
            default:
                break;
            }
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
    reg.emplace<Velocity>(ent, 0.0f, 0.0f);
    reg.emplace<DrawInfo>(ent, 10, 256);

    return ent;
}

auto run_systems(entt::registry &reg, float dt, SDL_Renderer *rend) -> void {
    movement_system(reg, dt);
    render_system(reg, rend);
}

auto main() -> int {
    auto t0  = std::chrono::high_resolution_clock::now();
    auto t1  = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    auto reg = entt::registry{};

    SDL_Init(SDL_INIT_VIDEO);
    auto window =
        SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_RESIZABLE);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    auto p = create_paddle(reg, w * 0.1, h / 2);
    reg.emplace<Player>(p);

    create_paddle(reg, w * 0.9, h / 2);

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event ev{};
    Input input{};

    while(!quit) {
        t0 = std::chrono::high_resolution_clock::now();

        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
            case SDL_QUIT:
                quit = true;
            case SDL_KEYDOWN:
                if(ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    quit = true;
                input.keys_down.emplace_back(ev.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                input.keys_up.emplace_back(ev.key.keysym.scancode);
                break;
            }
            player_input_system(reg, input);
            input.keys_up.clear();
            input.keys_down.clear();
        }
        run_systems(reg, dt, renderer);

        t1 = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        // dt /= 1000000.0;
        dt *= 0.000001;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}