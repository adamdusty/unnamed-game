#include "collision.hpp"

#include "fmt/format.h"

namespace pong {

auto box_collider(float x, float y, float w, float h, float rotation) -> PolygonCollider {
    return PolygonCollider{x,
                           y,
                           rotation,
                           std::vector<Point>{
                               {x, y},         // Top left
                               {x + w, y},     // Top right
                               {x + w, y + h}, // Bottom right
                               {x, y + h},     // Bottom left
                           }};
}

// TODO: Implement rotations
auto collision_detection(const PolygonCollider &col1,
                         const Transform &t1,
                         const PolygonCollider &col2,
                         const Transform &t2) -> CollisionType {

    // std::cout << "INPUT COLLIDER: " << col1.points.size() << '\n';
    std::vector<Point> col1_points{};
    std::vector<Point> col2_points{};

    // Get collider positions
    for(auto &p: col1.points) {
        col1_points.emplace_back(Point{p.x + t1.position.x, p.y + t1.position.y});
    }

    // Get collider positions
    for(auto &p: col2.points) {
        col2_points.emplace_back(Point{p.x + t2.position.x, p.y + t2.position.y});
    }

    // Check all axes from collider1
    for(int i = 0; i < col1_points.size(); i++) {
        int k = (i + 1) % col1_points.size();

        Point projection_axis{-(col1_points.at(k).y - col1_points.at(i).y), col1_points.at(k).x - col1_points.at(i).x};
        float mag       = sqrtf(projection_axis.x * projection_axis.x + projection_axis.y * projection_axis.y);
        projection_axis = {projection_axis.x / mag, projection_axis.y / mag};

        float min1 = INFINITY;
        float max1 = -INFINITY;

        for(auto &p: col1_points) {
            float projection = p.x * projection_axis.x + p.y * projection_axis.y;

            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        float min2 = INFINITY;
        float max2 = -INFINITY;

        for(auto &p: col2_points) {
            float projection = p.x * projection_axis.x + p.y * projection_axis.y;

            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if(!(max2 >= min1 && max1 >= min2))
            return CollisionType::None;
    }

    // Check all axes from collider2
    for(int i = 0; i < col2_points.size(); i++) {
        int k = (i + 1) % col2_points.size();

        Point projection_axis{-(col2_points.at(k).y - col2_points.at(i).y), col2_points.at(k).x - col2_points.at(i).x};
        float mag       = sqrtf(projection_axis.x * projection_axis.x + projection_axis.y * projection_axis.y);
        projection_axis = {projection_axis.x / mag, projection_axis.y / mag};

        float min1 = INFINITY;
        float max1 = -INFINITY;

        for(auto &p: col1_points) {
            float projection = p.x * projection_axis.x + p.y * projection_axis.y;

            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        float min2 = INFINITY;
        float max2 = -INFINITY;

        for(auto &p: col2_points) {
            float projection = p.x * projection_axis.x + p.y * projection_axis.y;

            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if(!(max2 >= min1 && max1 >= min2))
            return CollisionType::None;
    }

    return CollisionType::Overlapping;
}

} // namespace pong