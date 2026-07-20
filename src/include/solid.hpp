#ifndef _SOLID_HPP
#define _SOLID_HPP

#include "shape.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template <unsigned int dim> class RigidBody {
  const Point<dim> position;
  const std::vector<std::unique_ptr<Shape<dim>>> collision_shapes;
  const bool fixed = true;

public:
  RigidBody(const Point<dim> position_,
            std::vector<std::unique_ptr<Shape<dim>>> collision_shapes_)
      : position(position_), collision_shapes(std::move(collision_shapes_)) {}

  ~RigidBody() = default;

  bool isCollidingWith(const Point<dim> &point) const {
    for (const std::unique_ptr<Shape<dim>> &sh : collision_shapes) {
      if (sh->isCollidingWith(point))
        return true;
    }
    return false;
  };

  std::ostream &draw(std::ostream &out, int row, int width) {
    for (int x = 0; x < width; x++) {
      if (isCollidingWith({x, row})) {
        out << "*";
      } else {
        out << " ";
      }
    }

    return out;
  }
};

#endif // _SOLID_HPP
