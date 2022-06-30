#include "sys.hpp"

#include "collision.hpp"
#include "fmt/format.h"
#include <chrono>

namespace pong {

RenderSystem::RenderSystem(SDL_Window *window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

auto RenderSystem::run(entt::registry &reg, float dt) -> void {
    auto view = reg.view<const DrawInfo, const Transform>();

    SDL_RenderClear(renderer);

    SDL_Rect rect{};

    for(auto [e, d, t]: view.each()) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // rect.w = d.width;
        // rect.h = d.height;
        rect.x = t.position.x;
        rect.y = t.position.y;
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
}

auto RenderSystem::cleanup() -> void {
    SDL_DestroyRenderer(renderer);
}

auto debug_system(entt::registry &reg, float) -> void {
    auto view = reg.view<Debug, PolygonCollider, Transform>();
}

auto player_control_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<const Player, Velocity>();

    for(auto [e, p, v]: view.each()) {
        v.y = p.axis_input.at(1) * 256;
    }
}

auto player_input_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Player, Input>();

    for(auto [e, p, i]: view.each()) {
        for(auto k: i.keys_down) {
            switch(k) {
            case SDL_SCANCODE_W:
                p.axis_input.at(1) = -1;
                break;
            case SDL_SCANCODE_S:
                p.axis_input.at(1) = 1;
                break;
            default:
                break;
            }
        }
        for(auto k: i.keys_up) {
            switch(k) {
            case SDL_SCANCODE_W:
                if(p.axis_input.at(1) == -1)
                    p.axis_input.at(1) = 0;
                break;
            case SDL_SCANCODE_S:
                if(p.axis_input.at(1) == 1)
                    p.axis_input.at(1) = 0;
                break;
            default:
                break;
            }
        }
    }
}

auto physics_system(entt::registry &reg, float dt) -> void {}

auto input_system(entt::registry &reg, float dt) -> void {
    static SDL_Event ev{};

    auto view = reg.view<Input>();

    for(auto [e, i]: view.each()) {
        i.clear();
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
            case SDL_QUIT:
                std::exit(0);
            case SDL_KEYDOWN:
                if(ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    std::exit(0);
                i.keys_down.emplace_back(ev.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                i.keys_up.emplace_back(ev.key.keysym.scancode);
                break;
            default:
                break;
            }
        }
    }
}

auto movement_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Transform, const Velocity>();

    for(auto [e, t, v]: view.each()) {
        t.position.x += v.x * dt;
        t.position.y += v.y * dt;
    }
}

auto collision_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Transform, PolygonCollider>();

    for(auto [e1, t1, c1]: view.each()) {
        for(auto [e2, t2, c2]: view.each()) {
            if(e1 != e2) {
                auto col = collision_detection(c1, t1, c2, t2);
            }
        }
    }
}

} // namespace pong