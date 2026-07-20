#ifndef _SHAPE_HPP
#define _SHAPE_HPP

#include "point.hpp"

#include <stdexcept>
#include <vector>

template <unsigned int dim> class Shape {
public:
  virtual bool isCollidingWith(const Point<dim> &point) const { return false; }
  virtual bool contains(const Point<dim> &point) const { return false; }
  virtual std::vector<Point<dim>> getPerimeter() const {
    return std::vector<Point<dim>>();
  }
};

template <unsigned int dim> class Segment : public Shape<dim> {
  const Point<dim> start;
  const Point<dim> end;
  std::vector<Point<dim>> cached_perimeter;

public:
  Segment(const Point<dim> start_, const Point<dim> end_)
      : start(start_), end(end_) {}

  ~Segment() = default;

  bool isCollidingWith(const Point<dim> &point) const override {
    if constexpr (dim == 2) {
      return checkCollision(point);
    } else {
      return checkCollision(point);
    }
  }

  bool contains(const Point<dim> &point) const override {
    return isCollidingWith(point);
  }

private:
  bool checkCollision(const Point<2> &point) const {
    if (end.x - start.x == 0) {
      const int max_y = end.y > start.y ? end.y : start.y;
      const int min_y = end.y > start.y ? start.y : end.y;
      return point.x == end.x && point.y <= max_y && point.y >= min_y;
    }

    if (end.y - start.y == 0) {
      const int max_x = end.x > start.x ? end.x : start.x;
      const int min_x = end.x > start.x ? start.x : end.x;
      return point.y == end.y && point.x <= max_x && point.x >= min_x;
    }

    const double mu_x = static_cast<double>(point.x - start.x) /
                        static_cast<double>(end.x - start.x);
    const double mu_y = static_cast<double>(point.y - start.y) /
                        static_cast<double>(end.y - start.y);
    return mu_x == mu_y && mu_x >= 0 && mu_x <= 1;
  }

  bool checkCollision(const Point<3> &point) const {
    throw std::runtime_error("Collision Detection in 3D not yet implemented");
  }
};

// TODO: implement Circle-Point collision
template <unsigned int dim> class Circle : public Shape<dim> {};

// TODO: implement Rectangle-Point collision
template <unsigned int dim> class Rectangle : public Shape<dim> {};

#endif // _SHAPE_HPP
