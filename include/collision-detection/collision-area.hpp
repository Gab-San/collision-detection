#ifndef _SOLID_HPP
#define _SOLID_HPP

// COLLISION DETECTION LIB
#include "collision-detection/shape.hpp"

// C++ STANDARD LIB
#include <utility>
#include <variant>
#include <vector>

namespace lbm {
namespace CollisionDetection {

template <int dim>
using CollisionShapesT =
    std::variant<Segment<dim>, Circle<dim>, Parallelogram<dim>>;

template <unsigned int dim> class CollisionArea {

  const utils::Point<dim> position;
  const std::vector<CollisionShapesT<dim>> collision_shapes;
  mutable std::vector<utils::Point<dim>> cached_perimeter;
  const bool fixed = true;

public:
  CollisionArea(const utils::Point<dim> position_,
                std::vector<CollisionShapesT<dim>> collision_shapes_)
      : position(position_), collision_shapes(std::move(collision_shapes_)) {}

  ~CollisionArea() = default;

  bool isCollidingWith(const utils::Point<dim> &point) const {
    for (const auto &sh : collision_shapes) {
      bool hit = std::visit(
          [&](const auto &shape) {
            return shape.isCollidingWith(point - position);
          },
          sh);

      if (hit)
        return true;
    }
    return false;
  };

  bool contains(const utils::Point<dim> &point) const {
    for (const auto &sh : collision_shapes) {
      bool hit = std::visit(
          [&](const auto &shape) { return shape.contains(point - position); },
          sh);

      if (hit)
        return true;
    }
    return false;
  }

  const std::vector<utils::Point<dim>> &getPerimeter(bool force = false) const {
    if (!cached_perimeter.empty() && !force)
      return cached_perimeter;

    cached_perimeter.clear();
    for (const auto &sh : collision_shapes) {
      std::visit(
          [&](const auto &shape) {
            const auto &shape_perimeter = shape.getPerimeter();
            for (const auto &p : shape_perimeter) {
              cached_perimeter.emplace_back(position + p);
            }
          },
          sh);
    }
    return cached_perimeter;
  }
};

} // namespace CollisionDetection
} // namespace lbm

#endif // _SOLID_HPP
