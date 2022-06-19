#include "sys.hpp"

namespace pong {
auto movement_system(entt::registry &reg, float dt) -> void {
    auto view = reg.view<Position, Velocity>();

    for(auto [entity, pos, vel]: view.each()) {
        pos.x += vel.x * 500 * dt;
        pos.y += vel.y * 500 * dt;
    }
}

auto player_input_system(entt::registry &reg, const Input input) -> void {
    auto view = reg.view<Player, Velocity>();

    for(auto [e, p, v]: view.each()) {
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
    }
}

auto render_system(entt::registry &reg, SDL_Renderer *rend) -> void {
    auto view = reg.view<DrawInfo, PhysicsComponent>();

    SDL_RenderClear(rend);

    SDL_Rect rect{};

    for(auto [e, d, p]: view.each()) {
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        rect.w = d.quad.at(0);
        rect.h = d.quad.at(1);
        rect.x = p.body->GetPosition().x;
        rect.y = p.body->GetPosition().y;
        SDL_RenderFillRect(rend, &rect);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    }

    SDL_RenderPresent(rend);
}

auto physics_system(entt::registry &reg, float dt) -> void {
    if(entt::locator<b2World>::has_value()) {
        entt::locator<b2World>::value().Step(dt, 8, 3);
    }

    auto view = reg.view<Position, PhysicsComponent>();

    for(auto [e, pos, phy]: view.each()) {
        pos.x = phy.body->GetPosition().x;
        pos.y = phy.body->GetPosition().y;
    }
}

} // namespace pong