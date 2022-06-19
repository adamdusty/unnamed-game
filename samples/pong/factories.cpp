#include "factories.hpp"

#include "comp.hpp"
#include <random>

namespace pong {

auto create_paddle(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<Position>(ent, x, y);
    reg.emplace<Velocity>(ent, 0.0f, 0.0f);
    reg.emplace<DrawInfo>(ent, 10, 256);

    return ent;
}

auto create_ball(entt::registry &reg, float x, float y) -> entt::entity {
    auto ent = reg.create();
    reg.emplace<DrawInfo>(ent, 32, 32);

    b2BodyDef body_def{};
    body_def.type = b2_dynamicBody;
    body_def.position.Set(x, y);

    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixture{};
    fixture.shape    = &shape;
    fixture.density  = 1.0f;
    fixture.friction = 0.3f;

    // PhysicsComponent comp{body_def, fixture};
    auto &comp = reg.emplace<PhysicsComponent>(ent, body_def, fixture);

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<float> dis{10.0f, 20.0f};
    b2Vec2 vel{dis(gen), dis(gen)};
    comp.body->SetLinearVelocity(vel);

    reg.emplace<Position>(ent, comp.body->GetPosition().x, comp.body->GetPosition().y);

    return ent;
}

} // namespace pong