#pragma once

#include "SDL.h"
#include "box2d/box2d.h"
#include "entt/entt.hpp"
#include <array>
#include <functional>
#include <memory>
#include <vector>

struct Position {
    float x;
    float y;
};

struct Input {
    std::vector<SDL_Scancode> keys_down;
    std::vector<SDL_Scancode> keys_up;

    auto clear() -> void {
        keys_down.clear();
        keys_up.clear();
    }
};

struct Player {
    std::array<float, 2> axis_input;
};

struct DrawInfo {
    std::array<float, 2> quad;
};

struct PhysicsComponent {
    std::unique_ptr<b2Body, std::function<void(b2Body *)>> body;

    PhysicsComponent(const b2BodyDef &def, const b2FixtureDef &fixture) {
        body = {entt::locator<b2World>::value().CreateBody(&def), [](b2Body *b) {
                    entt::locator<b2World>::value().DestroyBody(b);
                }};

        body->CreateFixture(&fixture);
    }
};