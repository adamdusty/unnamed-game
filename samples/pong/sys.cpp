#include "sys.hpp"

#include "collision.hpp"
#include "fmt/format.h"
#include <chrono>

namespace pong {

SDLRenderSystem::SDLRenderSystem(SDL_Window *window) {
    next_texture = 0;
    renderer     = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDLRenderSystem::~SDLRenderSystem() {
    for(auto [k, v]: texture_map) {
        SDL_DestroyTexture(v);
    }
    texture_map.clear();
    SDL_DestroyRenderer(renderer);
}

auto SDLRenderSystem::create_texture(const Image &img) -> uint32_t {
    auto surface = SDL_CreateRGBSurfaceWithFormatFrom(
        img.data.get(), img.width, img.height, img.depth, img.pitch, SDL_PIXELFORMAT_RGBA32);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    texture_map.insert({next_texture, texture});
    return next_texture++;
}

auto SDLRenderSystem::execute(entt::registry &reg, float dt) -> void {
    auto view = reg.view<const SDLDrawInfo, const Transform>();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Rect src_rect{};
    SDL_Rect dst_rect{};

    for(auto [e, d, t]: view.each()) {
        dst_rect.x = t.position.x;
        dst_rect.y = t.position.y;
        dst_rect.w = d.width;
        dst_rect.h = d.height;

        SDL_RenderCopyEx(renderer, texture_map.at(d.texture), nullptr, &dst_rect, t.rotation, nullptr, SDL_FLIP_NONE);
    }

    auto debug_view = reg.view<const PolygonCollider, const Transform>();

    std::vector<SDL_FPoint> points{};
    // std::vector<SDL_FPoint> points{{250, 250}, {1000, 250}};
    for(auto [e, c, t]: debug_view.each()) {
        for(size_t i = 0; i < c.points.size() + 1; i++) {
            auto p = c.points.at(i % c.points.size());
            points.emplace_back(SDL_FPoint{p.x + t.position.x, p.y + t.position.y});
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLinesF(renderer, points.data(), points.size());
    }

    SDL_RenderPresent(renderer);
}

auto debug_system(entt::registry &reg, float) -> void {
    auto view = reg.view<Debug, PolygonCollider, Transform>();
}

auto player_control_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<const Player, Velocity>();

    for(auto [e, p, v]: view.each()) {
        v.y          = p.axis_input.at(1) * 256;
        v.rotational = p.axis_input.at(0) * 32;
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
        t.rotation += v.rotational * dt;
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