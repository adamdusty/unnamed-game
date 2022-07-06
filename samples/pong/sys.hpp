#pragma once

#include "comp.hpp"
#include "entt/entt.hpp"
#include "image.hpp"
#include "render.hpp"
#include <cstdint>
#include <unordered_map>

namespace pong {

struct SDLRenderSystem : public RenderSystem {

    SDLRenderSystem(SDL_Window *window);
    ~SDLRenderSystem();

    SDLRenderSystem(const SDLRenderSystem &other)            = delete; // Copy constructor
    SDLRenderSystem &operator=(const SDLRenderSystem &other) = delete; // Copy assignment operator

    SDLRenderSystem(SDLRenderSystem &&other) noexcept :
        renderer(std::exchange(other.renderer, nullptr)), texture_map(std::move(other.texture_map)),
        next_texture(other.next_texture) {}
    SDLRenderSystem &operator=(SDLRenderSystem &&other) noexcept {
        std::swap(renderer, other.renderer);
        std::swap(texture_map, other.texture_map);
        next_texture = other.next_texture;
        return *this;
    }

    auto execute(entt::registry &reg, float dt) -> void override;
    auto create_texture(const Image &img) -> uint32_t override;

    SDL_Renderer *renderer;
    std::unordered_map<uint32_t, SDL_Texture *> texture_map;
    uint32_t next_texture;
};

auto player_input_system(entt::registry &reg, float dt) -> void;
auto input_system(entt::registry &reg, float dt) -> void;
auto player_control_system(entt::registry &reg, float dt) -> void;
auto movement_system(entt::registry &reg, float dt) -> void;
auto collision_system(entt::registry &reg, float dt) -> void;
auto debug_system(entt::registry &reg, float dt) -> void;

} // namespace pong