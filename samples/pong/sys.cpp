#include "sys.hpp"

#include "collision.hpp"
#include "fmt/format.h"
#include <chrono>
#include <iostream>

namespace pong {

auto debug_system(entt::registry &reg, float) -> void {
    auto view = reg.view<Debug, PolygonCollider, Position>();

    // for(auto e: view) {
    //     auto &col = view.get<PolygonCollider>(e);
    //     auto &pos = view.get<Position>(e);

    //     fmt::print("POSITION: ({}, {})\n", pos.x, pos.y);
    //     for(auto &p: col.points) {
    //         Point adj{p.x + pos.x, p.y + pos.y};
    //         fmt::print("POINT: ({}, {})\n", adj.x, adj.y);
    //     }
    // }
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

auto render_system(entt::registry &reg, SDL_Renderer *rend) -> void {
    auto view = reg.view<const DrawInfo, const Position>();

    SDL_RenderClear(rend);

    SDL_Rect rect{};

    for(auto [e, d, p]: view.each()) {
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        rect.w = d.width;
        rect.h = d.height;
        rect.x = p.x;
        rect.y = p.y;
        SDL_RenderFillRect(rend, &rect);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    }

    SDL_RenderPresent(rend);
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
    auto view = reg.view<Position, const Velocity>();

    for(auto [e, p, v]: view.each()) {
        p.x += v.x * dt;
        p.y += v.y * dt;
    }
}

auto collision_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Position, PolygonCollider>();

    for(auto [e1, p1, c1]: view.each()) {
        for(auto [e2, p2, c2]: view.each()) {
            if(e1 != e2) {
                auto col = collider_overlap(c1, p1, c2, p2);
                if(col == CollisionType::Overlapping)
                    std::cout << "OVERLAPPING\n";
                // else
                //     std::cout << "NO OVERLAP\n";
            }
        }
    }
}

} // namespace pong