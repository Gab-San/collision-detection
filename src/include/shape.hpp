#ifndef _SHAPE_HPP
#define _SHAPE_HPP

#include "point.hpp"
#include "vector.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>

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
  const Vector<dim> AB;
  const Point<dim> A, B;
  mutable std::vector<Point<dim>> cached_perimeter;
  const double dist_x, dist_y;

public:
  Segment(const Point<dim> A_, const Point<dim> B_)
      : AB(A_, B_), A(A_), B(B_), dist_x(static_cast<double>(B.x - A.x)),
        dist_y(static_cast<double>(B.y - A.y)) {}

  ~Segment() = default;

  bool isCollidingWith(const Point<dim> &point) const {
    const Vector<dim> AP(A, point);
    const int dotAP_AB = dot(AP, AB);
    const int dotAB_AB = dot(AB, AB);

    return cross(AP, AB) == 0 && dotAP_AB >= 0 && dotAP_AB <= dotAB_AB;
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

    static_assert(false, "Circle::checkCollisionWith(Point<3>&) : "
                         "Collision Detection in 3D not yet implemented!");
  }
};

template <unsigned int dim>
class Parallelogram : public Shape<dim, Parallelogram<dim>> {
  const Point<dim> A, B, C, D;
  mutable std::vector<Point<dim>> cached_perimeter;

public:
  Parallelogram(const Point<dim> A_, const Point<dim> B_, const Point<dim> C_,
                const Point<dim> D_)
      : A(A_), B(B_), C(C_), D(D_) {
    Vector<dim> AB(A_, B_), BC(B_, C_), CD(C_, D_), DA(D_, A_);
    if (dot(AB, CD) != 1 || dot(BC, DA) != 1) {
      throw std::invalid_argument(
          "Parallelogram : opposite sides not parallel");
    }
  }

  bool isCollidingWith(const Point<dim> &point) const {
    Segment<dim> sideAB(A, B);
    Segment<dim> sideBC(B, C);
    Segment<dim> sideCD(C, D);
    Segment<dim> sideDA(D, A);

    bool hit = sideAB.isCollidingWith(point) || sideBC.isCollidingWith(point) ||
               sideCD.isCollidingWith(point) || sideDA.isCollidingWith(point);

    return hit;
  }

  bool contains(const Point<dim> &point) const {
    const Vector<dim> AB(A, B), AD(A, D), AP(A, point);

    const int dotAB_AB = dot(AB, AB);
    const int dotAP_AB = dot(AP, AB);
    const int dotAD_AD = dot(AD, AD);
    const int dotAP_AD = dot(AP, AD);

    // The dot product can be considered the module of the projection
    // of vector AP onto the target vector (AB, AD).
    // The projection of a vector onto itself (if normalized) is equal to 1.
    // The projection of any other vector will be between [-1, 1).
    //
    // In this case we check that the projection of the vector is positive and
    // it is less then the projection of the target vector onto itself (if
    // normalized this would correspond to checking that the projection lies in
    // [0,1]).
    return dotAP_AB >= 0 && dotAP_AB <= dotAB_AB && dotAP_AD >= 0 &&
           dotAP_AD <= dotAD_AD;
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
