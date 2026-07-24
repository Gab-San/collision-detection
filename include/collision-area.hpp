#ifndef __COLLISION_AREA_HPP
#define __COLLISION_AREA_HPP

// COLLISION DETECTION LIB
#include "shape.hpp"

#include "types/common.hpp"

// C++ STANDARD LIB
#include <utility>
#include <variant>
#include <vector>

namespace CollisionDetection {

template <int dim>
using CollisionShapesT =
    std::variant<Segment<dim>, Circle<dim>, Parallelogram<dim>>;

template <unsigned int dim> class CollisionArea {

  types::Coordinate<dim> position;
  const std::vector<CollisionShapesT<dim>> collision_shapes;
  mutable std::vector<types::Coordinate<dim>> cached_perimeter;

public:
  CollisionArea(const types::Coordinate<dim> position_,
                std::vector<CollisionShapesT<dim>> collision_shapes_)
      : position(position_), collision_shapes(std::move(collision_shapes_)) {}

  ~CollisionArea() = default;

  bool isCollidingWith(const types::Coordinate<dim> &point) const {
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

  bool contains(const types::Coordinate<dim> &point) const {
    for (const auto &sh : collision_shapes) {
      bool hit = std::visit(
          [&](const auto &shape) { return shape.contains(point - position); },
          sh);

      if (hit)
        return true;
    }
    return false;
  }

  const std::vector<types::Coordinate<dim>> &
  getPerimeter(bool force = false) const {
    if (!cached_perimeter.empty() && !force)
      return cached_perimeter;

    cached_perimeter.clear();
    for (const auto &sh : collision_shapes) {
      std::visit(
          [&](const auto &shape) {
            const auto &shape_perimeter = shape.getPerimeter();
            for (const auto &p : shape_perimeter) {
              if (std::find(cached_perimeter.begin(), cached_perimeter.end(),
                            p) != cached_perimeter.end()) {
                cached_perimeter.emplace_back(position + p);
              }
            }
          },
          sh);
    }
    return cached_perimeter;
  }
};

} // namespace CollisionDetection

#endif // _SOLID_HPP
