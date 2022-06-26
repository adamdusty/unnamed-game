#pragma once

#include "comp.hpp"
#include "utils.hpp"
#include <iostream>
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
};

auto box_collider(float x, float y, float w, float h, float rotation = 0.0f) -> PolygonCollider;

auto collider_overlap(const PolygonCollider &col1,
                      const Position &pos1,
                      const PolygonCollider &col2,
                      const Position &pos2) -> CollisionType;

} // namespace pong