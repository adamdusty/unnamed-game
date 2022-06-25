#include "factories.hpp"

#include "comp.hpp"
#include <random>

namespace pong {

auto create_paddle(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<DrawInfo>(ent, 32 / 32.0f, 256 / 32.0f);

    b2BodyDef body_def{};
    body_def.type = b2_dynamicBody;
    body_def.position.Set(x, y);

    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixture{};
    fixture.shape    = &shape;
    fixture.density  = 1.0f;
    fixture.friction = 0.3f;

    auto &comp = reg.emplace<PhysicsComponent>(ent, body_def, fixture);
    reg.emplace<Position>(ent, comp.body->GetPosition().x, comp.body->GetPosition().y);

    return ent;
}

auto create_ball(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<DrawInfo>(ent, 32 / 32.0f, 32 / 32.0f);

    b2BodyDef body_def{};
    body_def.type = b2_dynamicBody;
    body_def.position.Set(x, y);

    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixture{};
    fixture.shape    = &shape;
    fixture.density  = 1.0f;
    fixture.friction = 0.3f;

    auto &comp = reg.emplace<PhysicsComponent>(ent, body_def, fixture);

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<float> dis{40.0f, 80.0f};
    b2Vec2 vel{dis(gen), dis(gen)};
    comp.body->SetLinearVelocity(vel);

    reg.emplace<Position>(ent, comp.body->GetPosition().x, comp.body->GetPosition().y);

    return ent;
}

} // namespace pong