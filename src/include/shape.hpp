#ifndef _SHAPE_HPP
#define _SHAPE_HPP

#include "point.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>

// FIXME: Position isn't relative to parent RigidBody
// FIXME: Should be extendible to 3D

template <unsigned int dim, class DerivedShape> class Shape {
public:
  bool isCollidingWith(const Point<dim> &point) const {
    return static_cast<DerivedShape *>(this)->isCollidingWith(point);
  };

  bool contains(const Point<dim> &point) const {
    return static_cast<DerivedShape *>(this)->contains(point);
  };

  std::vector<Point<dim>> &getPerimeter() const {
    return static_cast<DerivedShape *>(this)->getPerimeter();
  };

protected:
  Shape() = default;
};

template <unsigned int dim> class Segment : public Shape<dim, Segment<dim>> {
  const Point<dim> A, B;
  mutable std::vector<Point<dim>> cached_perimeter;
  const double dist_x, dist_y;

public:
  Segment(const Point<dim> A_, const Point<dim> B_)
      : A(A_), B(B_), dist_x(static_cast<double>(B.x - A.x)),
        dist_y(static_cast<double>(B.y - A.y)) {}

  ~Segment() = default;

  bool isCollidingWith(const Point<dim> &point) const {
    if constexpr (dim == 2) {
      return checkCollisionWith(point);
    } else {
      return checkCollisionWith(point);
    }
  }

  bool contains(const Point<dim> &point) const {
    return isCollidingWith(point);
  }

  std::vector<Point<dim>> &getPerimeter() const {
    if (!cached_perimeter.empty()) {
      return cached_perimeter;
    }

    cached_perimeter.clear();

    if (B.x - A.x == 0) {
      const bool isneg = (B.y - A.y) < 0;
      const int end = isneg ? A.y - (B.y - A.y) : B.y;

      for (int y = A.y; y <= end; y++) {
        const int dist = isneg ? 2 * (y - A.y) : 0;
        cached_perimeter.push_back(Point<dim>(A.x, y - dist));
      }

      return cached_perimeter;
    }

    if (B.y - A.y == 0) {
      const bool isneg = (B.x - A.x) < 0;
      const int end = isneg ? A.x - (B.x - A.x) : B.x;

      for (int x = A.x; x <= end; x++) {
        const int dist = isneg ? 2 * (x - A.x) : 0;
        cached_perimeter.push_back(Point<dim>(x - dist, A.y));
      }

      return cached_perimeter;
    }

    // FIXME: This does not match the expected results
    if constexpr (std::abs(B.x - A.x) < std::abs(B.y - A.y)) {
      const int max_x = B.x > A.x ? B.x : A.x;
      const int min_x = B.x > A.x ? A.x : B.x;

      for (int x = min_x; x <= max_x; x++) {
        const double k_y = (x - A.x) / dist_x;
        const int y = A.y + k_y * (B.y - A.y);
        cached_perimeter.push_back(Point<dim>(x, y));
      }
    } else {
      const int max_y = B.y > A.y ? B.y : A.y;
      const int min_y = B.y > A.y ? A.y : B.y;

      for (int y = min_y; y <= max_y; y++) {
        const double k_x = (y - A.y) / dist_y;
        const int x = A.x + k_x * (B.x - A.x);
        cached_perimeter.push_back(Point<dim>(x, y));
      }
    }
    return cached_perimeter;
  }

private:
  bool checkCollisionWith(const Point<2> &point) const {
    if (B.x - A.x == 0) {
      const int max_y = B.y > A.y ? B.y : A.y;
      const int min_y = B.y > A.y ? A.y : B.y;
      // If vertical line check that Ymin <= Yp <= Ymax and Xp == Xseg
      return point.x == B.x && point.y <= max_y && point.y >= min_y;
    }

    if (B.y - A.y == 0) {
      const int max_x = B.x > A.x ? B.x : A.x;
      const int min_x = B.x > A.x ? A.x : B.x;
      // If horizontal line check that Xmin <= Xp <= Xman & Yp == Yseg
      return point.y == B.y && point.x <= max_x && point.x >= min_x;
    }

    // Check that slope on both X and Y is the same and it is
    // between 0 and 1

    const double k_x = (point.x - A.x) / dist_x;
    const double k_y = (point.y - A.y) / dist_y;
    return k_x == k_y && k_x >= 0 && k_x <= 1;
  }

  bool checkCollisionWith(const Point<3> &point) const {
    throw std::runtime_error("Segment::checkCollisionWith : Collision "
                             "Detection in 3D not yet implemented");
  }
};

template <unsigned int dim> class Circle : public Shape<dim, Circle<dim>> {
  const Point<dim> center;
  const unsigned int radius;
  mutable std::vector<Point<dim>> cached_perimeter;

public:
  Circle(const Point<dim> center_, const unsigned int radius_)
      : center(center_), radius(radius_) {}

  bool isCollidingWith(const Point<dim> &point) const {
    if constexpr (dim == 2) {
      return checkCollisionWith(point);
    } else {
      return checkCollisionWith(point);
    }
  }

  bool contains(const Point<dim> &point) const {
    const int center_point_dist_x = center.x - point.x;
    const unsigned int dist_x = center_point_dist_x * center_point_dist_x;
    const int center_point_dist_y = center.y - point.y;
    const unsigned int dist_y = center_point_dist_y * center_point_dist_y;

    return dist_x + dist_y <= radius * radius;
  }

  std::vector<Point<dim>> &getPerimeter() const {
    if (!cached_perimeter.empty()) {
      return cached_perimeter;
    }

    cached_perimeter.clear();

    int x = -radius;
    int y = 0;
    cached_perimeter.push_back(center + Point<dim>(x, y));
    cached_perimeter.push_back(center + Point<dim>(-x, y));

    cached_perimeter.push_back(center + Point<dim>(0, radius));
    cached_perimeter.push_back(center + Point<dim>(0, -radius));

    while (x < static_cast<int>(radius)) {
      if (x < 0) {
        if (x * x + (y + 1) * (y + 1) > radius * radius) {
          x++;
        } else {
          y++;
        }
      } else {
        if ((x + 1) * (x + 1) + y * y > radius * radius) {
          y--;
        } else {
          x++;
        }
      }

      if (y == -y) {
        continue;
      }

      cached_perimeter.push_back(center + Point<dim>(x, y));
      cached_perimeter.push_back(center + Point<dim>(x, -y));
    }

    return cached_perimeter;
  }

private:
  bool checkCollisionWith(const Point<2> &point) const {
    const int center_point_dist_x = center.x - point.x;
    const unsigned int dist_x = center_point_dist_x * center_point_dist_x;
    const int center_point_dist_y = center.y - point.y;
    const unsigned int dist_y = center_point_dist_y * center_point_dist_y;

    return dist_x + dist_y == radius * radius;
  }

  bool checkCollisionWith(const Point<3> &point) const {
    throw std::runtime_error("Circle::checkCollisionWith(Point<3>&) : "
                             "Collision Detection in 3D not yet implemented!");
  }
};

#include <iostream>

// TODO: implement Rectangle-Point collision
template <unsigned int dim>
class Rectangle : public Shape<dim, Rectangle<dim>> {
  const Point<dim> A, B, C, D;
  mutable std::vector<Point<dim>> cached_perimeter;

public:
  Rectangle(const Point<dim> A_, const Point<dim> C_)
      : Rectangle(A_, Point<dim>(A_.x, C_.y), C_, Point<dim>(C_.x, A_.y)) {}

  Rectangle(const Point<dim> A_, const Point<dim> B_, const Point<dim> C_,
            const Point<dim> D_)
      : A(A_), B(B_), C(C_), D(D_) {}

  bool isCollidingWith(const Point<dim> &point) const {
    Segment<dim> sideAB(A, B);
    Segment<dim> sideBC(B, C);
    Segment<dim> sideCD(C, D);
    Segment<dim> sideDA(D, A);

    bool hit = sideAB.isCollidingWith(point) || sideBC.isCollidingWith(point) ||
               sideCD.isCollidingWith(point) || sideDA.isCollidingWith(point);

    return hit;
  }

  // FIXME: This does not take into account inner points
  bool contains(const Point<dim> &point) const {
    const int max_x = A.x > D.x ? A.x : D.x;
    const int min_x = max_x == A.x ? D.x : A.x;

    const int max_y = A.y > B.y ? A.y : B.y;
    const int min_y = max_y == A.y ? B.y : A.y;

    return point.x >= min_x && point.x <= max_x && point.y >= min_y &&
           point.y <= max_y;
  }

  std::vector<Point<dim>> &getPerimeter() const {
    if (!cached_perimeter.empty()) {
      return cached_perimeter;
    }

    cached_perimeter.clear();
    Segment<dim> sideAB(A, B);
    Segment<dim> sideBC(B, C);
    Segment<dim> sideCD(C, D);
    Segment<dim> sideDA(D, A);

    for (const auto &p : sideAB.getPerimeter()) {
      cached_perimeter.push_back(p);
    }
    for (const auto &p : sideBC.getPerimeter()) {
      cached_perimeter.push_back(p);
    }
    for (const auto &p : sideCD.getPerimeter()) {
      cached_perimeter.push_back(p);
    }
    for (const auto &p : sideDA.getPerimeter()) {
      cached_perimeter.push_back(p);
    }

    return cached_perimeter;
  }
};

#endif // _SHAPE_HPP
