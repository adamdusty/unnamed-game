#pragma once

#include "comp.hpp"
#include "utils.hpp"
#include <vector>

namespace pong {

enum class CollisionType {
    None,
    Overlapping,
    Touching,
};

struct PolygonCollider {
    float offset_x;
    float offset_y;
    float rotation;
    std::vector<Point> points;

    auto get_bounding_box() const -> std::vector<Point>;
};

auto box_collider(float x, float y, float w, float h, float rotation = 0.0f) -> PolygonCollider;

auto collision_detection(const PolygonCollider &col1,
                         const Transform &pos1,
                         const PolygonCollider &col2,
                         const Transform &pos2) -> CollisionType;

// TODO: collision_resolution

} // namespace pong