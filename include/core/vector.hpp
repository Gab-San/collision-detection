#ifndef __CORE_VECTOR_HPP
#define __CORE_VECTOR_HPP

// COLLISION DETECTION LIB
#include "core/point.hpp"

// C++ STANDARD LIB
#include <iostream>

namespace CollisionDetection {
namespace utils {

template <typename T, unsigned int dim> struct Vector;

template <typename T> struct Vector<T, 2> {
  T dx, dy;

  Vector() : dx(0), dy(0) {}
  Vector(const T &x, const T &y) : dx(x), dy(y) {}
  Vector(const Point<T, 2> &A_, const Point<T, 2> &B_)
      : Vector(B_.x - A_.x, B_.y - A_.y) {}

  // ---- OPERATOR OVERLOADING ----
  template <typename K>
  inline friend Vector<T, 2> operator+(const Vector<T, 2> &lhs,
                                       const Vector<K, 2> &rhs) {
    return Vector(lhs.dx + rhs.dx, lhs.dy + rhs.dy);
  }

  template <typename K>
  inline friend Vector<T, 2> &operator+=(const Vector<T, 2> &lhs,
                                         const Vector<K, 2> &rhs) {
    lhs.dx += rhs.dx;
    lhs.dy += rhs.dy;
    return lhs;
  }

  inline friend Vector<T, 2> operator-(const Vector<T, 2> &lhs,
                                       const Vector<T, 2> &rhs) {
    return Vector(lhs.dx - rhs.dx, lhs.dy - rhs.dy);
  }

  inline friend Point<T, 2> operator-(const Point<T, 2> &lhs,
                                      const Vector<T, 2> &rhs) {
    return Point(lhs.x - rhs.dx, lhs.y - rhs.dy);
  }

  inline friend std::ostream &operator<<(std::ostream &out,
                                         const Vector<T, 2> &v) {
    return out << "Vector(" << v.dx << "," << v.dy << ")";
  }

  // ---- OPERATION BY SCALAR ----
  template <typename K>
  inline friend Vector<T, 2> operator*(const Vector<T, 2> &lhs,
                                       const K &scalar) {
    return Vector(lhs.dx * scalar, lhs.dy * scalar);
  }

  template <typename K>
  inline friend Vector<T, 2> &operator/=(const Vector<T, 2> &lhs,
                                         const K &scalar) {

    lhs.dx /= scalar;
    lhs.dy /= scalar;
    return lhs;
  }
};

template <typename T, typename K, unsigned int dim>
const int dot(const Vector<T, dim> &lhs, const Vector<K, dim> &rhs) {
  if constexpr (dim == 2) {
    return lhs.dx * rhs.dx + lhs.dy * rhs.dy;
  } else {
    static_assert(false, "dot() : operator not yet implemented for 3D");
  }
}

template <typename T, typename K, unsigned int dim>
const int cross(const Vector<T, dim> &lhs, const Vector<K, dim> &rhs) {
  if constexpr (dim == 2) {
    return lhs.dx * rhs.dy - lhs.dy * rhs.dx;
  } else {
    static_assert(false, "cross() : operator not yet implemented for 3D");
  }
}

} // namespace utils
} // namespace CollisionDetection

#endif // __CORE_VECTOR_HPP
