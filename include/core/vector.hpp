#ifndef _VECTOR_HPP
#define _VECTOR_HPP

// COLLISION DETECTION LIB
#include "core/point.hpp"

// C++ STANDARD LIB
#include <iostream>

namespace lbm {
namespace utils {

template <int dim> struct Vector;

template <> struct Vector<2> {
  const int dx, dy;

  Vector(const int &x, const int &y) : dx(x), dy(y) {}
  Vector(const Point<2> &A_, const Point<2> &B_)
      : Vector(B_.x - A_.x, B_.y - A_.y) {}

  // ---- OPERATOR OVERLOADING ----
  inline friend Vector<2> operator-(const Vector<2> &lhs,
                                    const Vector<2> &rhs) {
    return Vector(lhs.dx - rhs.dx, lhs.dy - rhs.dy);
  }

  inline friend std::ostream &operator<<(std::ostream &out,
                                         const Vector<2> &v) {
    return out << "Vector(" << v.dx << "," << v.dy << ")";
  }
};

// template <> struct Vector<2> {
//   const Point<2>
// };

template <int dim>
const int dot(const Vector<dim> &lhs, const Vector<dim> &rhs) {
  if constexpr (dim == 2) {
    return lhs.dx * rhs.dx + lhs.dy * rhs.dy;
  } else {
    static_assert(false, "dot() : operator not yet implemented for 3D");
  }
}

template <int dim>
const int cross(const Vector<dim> &lhs, const Vector<dim> &rhs) {
  if constexpr (dim == 2) {
    return lhs.dx * rhs.dy - lhs.dy * rhs.dx;
  } else {
    static_assert(false, "cross() : operator not yet implemented for 3D");
  }
}

} // namespace utils
} // namespace lbm

#endif // _VECTOR_HPP
